#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;

#include <core/cli/parse.h>
#include "scp_matrix.h"
#include "set_covering_problem.h"

/**
 * Função de execução d programa principal inteiro
 */
int exec(CLI *args) {

  SetCoveringProblem scp("/home/ronaldd/Projects/crossover-study/data/scp41.txt");
  scp.display_info(std::cout);

  return 0;
}


/**
 * Função principal:
 * Encapsula a execução do programa todo com um bloco try/catch para
 * lidar com possíveis exceções não tratadas
 */
int main(int argc, char **argv) {
  try {
    CLI* arguments = parse(argc, argv);
    return exec(arguments);
  }
  catch (std::exception& e) {
    std::cerr << "Exception at[main()]: \"" << e.what() << "\"" << std::endl;
    return 1;
  }
  return 0;
}