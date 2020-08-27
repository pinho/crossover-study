#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;

#include <core/cli/parse.h>
#include "scp_matrix.h"
#include "set_covering_problem.h"

void break_lines(std::ostream &os, unsigned short __n = 60) {
  unsigned short n = 0;
  while (n++ < __n)
    os << '-';
  os << std::endl;
}

const char* trim_filename(const char *filename) {
  std::string str_filename(filename);
  return (split(str_filename, '/').end()-1)->c_str();
}

/**
 * Função de execução d programa principal inteiro
 */
int exec(CLI *args) {
  const char *fname = trim_filename(args->infile);
  std::cout << "Cobertura de conjuntos: " << fname << std::endl;
  break_lines(std::cout);

  SetCoveringProblem prob(args->infile);
  prob.display_info(std::cout);
  break_lines(std::cout);

  // TODO: Implementar AG

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
    std::cerr << "Exception at main(): \"" << e.what() << "\"" << std::endl;
    return 1;
  }
  return 0;
}