#include <iostream>
#include <ga/encoding.h>
#include <ga/random.h>

#include "set_covering_problem.h"
using SCP = SetCoveringProblem;

// TODO: Começar a implementar o tratamento do SCP

int main(int argc, char **argv)
{
    auto scp = new SCP(argv[1]);
    scp->display_info(std::cout);

    

    return 0;
}