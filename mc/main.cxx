#include <iostream>
#include <string>

#include "argparser.h"
#include "boolean_matrix.h"

matrix *M;

int main(int argc, char **argv) {
  try {
    parse_args(argc, argv);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  const char *pathToFile = posFilepath.Get().c_str();

  M = matrix::read_from_file(pathToFile);

  std::cout << M->size() << " linhas" << std::endl;

  return 0;
}