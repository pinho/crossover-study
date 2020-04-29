#include <iostream>
#include <algorithm>
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

// TODO: Começar a implementar o tratamento do SCP
int main(int argc, char **argv) {
    auto cli = parse(argc, argv);
    try {
        SCP scp(cli->infile);
        scp.display_info(std::cout);

        // create a population
        auto population = scp.init_pop(cli->pop_size);

        // evaluating the initial population
        std::cout << "Evaluating the initial population... ";
        scp.eval(population);
        std::cout << "DONE" << std::endl;

        // build GA components
        eoGenContinue<Chrom> continuator(cli->epochs);
        eoDetTournamentSelect<Chrom> selector(8);
        eoBitMutation<Chrom> mutator(cli->mutation_rate);

        // Choose crossover operator
        eoQuadOp<Chrom> *crossover_ptr = CrossoverFabric::create(64);

        // Genetic Algorithm object
        GeneticAlgorithm ga(scp, selector, *crossover_ptr, cli->crossover_rate,
                mutator, 1, continuator);

        // start algorithm
        ga(population, [](int g, eoPop<Chrom>& p) {
            std::cout << g << "a geração:\n";
            auto best_it = p.it_best_element();
            solution_t decoded_solution(*best_it);
            std::cout << "...." << decoded_solution << "\n";
        });

        // Get best solution
        Chrom best = population.best_element();
        solution_t final_solution(best);
        
        std::cout << "\nFinal Solution:" << std::endl;
        std::cout << final_solution.num_columns << " columns with a total cost = "
                << final_solution.cost << "\n";

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}