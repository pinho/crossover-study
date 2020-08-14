#include <cstdlib>
#include <iostream>
#include <core/cli/parse.h>
#include "steiner_tree.h"
#include "graph.h"

/**
 * Printa uma sequência de traços para separar linhas de log */
void sep_line(unsigned int n) {
  size_t i = 0;
  do { std::cout << "-"; } while (i++ < n);
  std::cout << std::endl;
}

int exec(CLI *args) {
  sep_line(60);
  std::cout << "Parâmetros:\n";
  std::cout << *args;

  SteinerTreeProblem stein("../src/st/steinb1.txt");
  sep_line(60);
  stein.display_info(std::cout);

  sep_line(60);
  std::cout << "Inicializando população" << std::flush;
  auto population = stein.init_pop( args->pop_size );
  std::cout << "\rPopulação inicial construída!" << std::endl;
  std::cout << population << std::endl;

  return 0;
}

// MAIN FUNCTION

int main(int argc, char **argv) {
  try {
    CLI* args = parse(argc, argv);
    return exec(args);
  } catch (std::exception &e) {
    std::cerr << "Main was catched: " << e.what() << std::endl;
    return 127;
  }
  return 0;
}