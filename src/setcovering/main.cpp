#include <iostream>
#include <ga/encoding.h>
#include <ga/crossover_fabric.h>
#include <ga/genetic_algorithm.h>
#include <cli/parse.h>

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>

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

        // Genetic Algorithm object
        GeneticAlgorithm ga(scp, selector, *crossover_ptr, cli->crossover_rate,
                mutator, 1, continuator);

        // start algorithm
        ga(population, [](int g, eoPop<Chrom>& p) {
            std::cout << g << "a geração: ";
            auto best_it = p.it_best_element();
            solution_t decoded_solution(*best_it);
            std::cout << ".... " << decoded_solution << "\n";
        });

        // Get best solution
        Chrom best = population.best_element();
        solution_t final_solution(best);
        
        std::cout << "\nSolução final:" << std::endl;
        std::cout << final_solution.num_columns << " colunas com um custo total de "
                << final_solution.cost << "\n";

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}