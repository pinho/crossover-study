#include <iostream>
#include <algorithm>
#include <ga/encoding.h>
#include <cli/parse.h>
#include "set_covering_problem.h"
#include "solution.h"

using SCP = SetCoveringProblem;

// TODO: Começar a implementar o tratamento do SCP
int main(int argc, char **argv) {
    auto cli = parse(argc, argv);

    try {

        SCP scp(cli->infile);
        scp.display_info(std::cout);

        auto population = scp.init_pop(8);
        scp.eval(population);
        population.sort();

        std::for_each(population.begin(), population.end(), [](Chrom& x) {
            std::cout << solution_t(x) << std::endl;
        });

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}