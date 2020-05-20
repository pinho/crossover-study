#include <iostream>
#include <cli/parse.h>
#include <ga/genetic_algorithm.h>
#include <ga/crossover_fabric.h>
#include <db/database_entry.hpp>

#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
#include <sqlite/connection.hpp>
#include <sqlite/database_exception.hpp>

#include "solution.h"
#include "maximum_clique_problem.h"
using MCP = MaximumCliqueProblem;

int main(int argc, char **argv) {
    auto cli = parse(argc, argv);

    try {
        // Problem instatiation
        auto maxclique = new MCP( cli->infile );
        maxclique->display_info(std::cout);
        // std::cout << *cli;

        // Create and evaliate initial population
        std::cout << "Inicializando e avaliando população inicial..."
                << std::flush;

        auto population = maxclique->init_pop( cli->pop_size );
        maxclique->eval(population);
        std::cout << "FEITO" << std::endl;

        // Create GA components
        eoGenContinue<Chrom> cont( cli->epochs );
        eoBitMutation<Chrom> mutation( cli->mutation_rate );
        eoDetTournamentSelect<Chrom> select(8);

        // Choice Crossover Operator
        auto crossover_ptr = CrossoverFabric::create( cli->crossover_id );
        auto crossover_name = CrossoverFabric::name( cli->crossover_id );
        std::cout << crossover_name << std::endl;

        // Genetic Algorithm
        GeneticAlgorithm ga(*maxclique, select, *crossover_ptr,
                cli->crossover_rate, mutation, cli->mutation_rate, cont);

        // Array for save convergence
        std::vector<Chrom> array_convergence;

        auto begin_point = std::chrono::system_clock::now();

        ga(population, array_convergence, [](int g, auto &pop) {
            std::cout << g << "a geração: ";
            std::cout << "clique de " << pop.best_element().fitness() << " nós"
                    << std::endl;
        });

        auto duration = std::chrono::system_clock::now() - begin_point;

        /**
         * Tratamento da solução final encontrada
         */
        auto best = population.best_element();
        auto final_solution = new mcp::solution_t( best );
        std::cout << "\nMelhor solução final: " << final_solution->num_nodes
                << " vértices\nÍndices: ";
        for (uint& n : final_solution->nodes) {
            std::cout << n << " ";
        }
        std::cout << std::endl << std::endl;

        auto g = maxclique->get_graph();

        for (uint& i : final_solution->nodes) {
            auto v = boost::vertices(*g).first + i;
            std::cout << *v << "\t";
            for (uint& j : final_solution->nodes) {
                auto u = boost::vertices(*g).first + j;
                auto edge = boost::edge(*v, *u, *g);
                std::cout << edge.second << " " << std::flush;
            }
            std::cout << std::endl;
        }

        // Executando a escrita dos dados de execução no banco de dados
        if (cli->using_db) {
            std::vector<double> fits;
            auto it = array_convergence.begin();
            for (; it != array_convergence.end(); ++it)
                fits.push_back( it->fitness() );

            DatabaseEntry entry(maxclique->name(), maxclique->acronym(),
                    cli->infile, crossover_name.c_str(), cli->crossover_rate, 
                    cli->pop_size, cli->epochs, final_solution->num_nodes,
                    fits, duration);

            sqlite::connection con(cli->databasefile);
            entry.write(con);
            std::cout << "Dados salvos em " << cli->databasefile << std::endl;
        }
    }
    catch (sqlite::database_exception &e) {
        std::cerr << "Erro de banco de dados: " << e.what() << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
