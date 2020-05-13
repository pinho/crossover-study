#include <iostream>
#include <chrono>
#include <algorithm>
#include <ga/encoding.h>
#include <ga/crossover_fabric.h>
#include <ga/genetic_algorithm.h>
#include <cli/parse.h>
#include <db/database_entry.hpp>
// ParadisEO
#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
// VSQLite++
#include <sqlite/connection.hpp>
#include <sqlite/database_exception.hpp>

#include "set_covering_problem.h"
#include "solution.h"

using SCP = SetCoveringProblem;

int main(int argc, char **argv) {
    auto cli = parse(argc, argv);
    try {
        SCP scp(cli->infile);
        scp.display_info(std::cout);
        std::cout << *cli;

        // create a population
        std::cout << "Inicializando população\n";
        auto population = scp.init_pop(cli->pop_size);

        // evaluating the initial population
        std::cout << "Avaliando população inicial... ";
        scp.eval(population);
        std::cout << "FEITO" << std::endl;

        // build GA components
        eoGenContinue<Chrom> continuator(cli->epochs);
        eoDetTournamentSelect<Chrom> selector(8);
        eoBitMutation<Chrom> mutator(cli->mutation_rate);

        // Choose crossover operator
        eoQuadOp<Chrom> *crossover_ptr = CrossoverFabric::create(cli->crossover_id);
        auto crossover_name = CrossoverFabric::name(cli->crossover_id);

        // Genetic Algorithm object
        GeneticAlgorithm ga(scp, selector, *crossover_ptr, cli->crossover_rate,
                mutator, 1, continuator);
        
        // Array for ga's convergence
        std::vector<Chrom> vec_convergence;

        // start algorithm
        auto begin_point = std::chrono::system_clock::now();

        ga(population, vec_convergence, [](int g, eoPop<Chrom>& p) {
            std::cout << g << "a geração: ";
            auto best_it = p.it_best_element();
            solution_t decoded_solution(*best_it);
            std::cout << ".... " << decoded_solution << "\n";
        });

        auto duration = std::chrono::system_clock::now() - begin_point;

        // Get best solution
        Chrom best = population.best_element();
        solution_t final_solution(best);
        
        std::cout << "\nSolução final:" << std::endl;
        std::cout << final_solution.num_columns
                  << " colunas com um custo total de "
                  << final_solution.cost << "\n";

        // Write to Database if is defined [--db]
        if (cli->using_db) {
            // Create a vector with the fitness of convergence
            std::vector<double> fitnesses(vec_convergence.size());
            for (auto i = vec_convergence.begin(); i != vec_convergence.end(); ++i) {
                solution_t s{*i};
                fitnesses.push_back(s.cost);
            }
            // Create a instance to put in DB table
            DatabaseEntry entry(scp.name(), scp.acronym(), cli->infile,
                    crossover_name, cli->crossover_rate, cli->pop_size,
                    cli->epochs, final_solution.cost, fitnesses, duration);
            
            // Connect to DB and Write data
            sqlite::connection conn( cli->databasefile );
            entry.write(conn);
            std::cout << "Dados salvos em " << cli->databasefile << std::endl;
        }
    }
    catch (sqlite::database_exception &sqle) {
        std::cerr << cli->databasefile << ": " << sqle.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
