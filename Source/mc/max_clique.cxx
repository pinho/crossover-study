#include "../macros.h"
#include "../problems.hxx"

#include <iostream>
#include <fstream>
#include <string>
#include <paradiseo/eo/ga/eoBit.h>

#include "matrix.h"

using Chrom = eoBit<int>;

void problem::max_clique(int argc, char **argv) {
  PRINT_GREEN("Problema do clique máximo");
  PRINT("\n");

  try {
    matrix *A = matrix::read_from_file("../instances/clique/fb-pages-food.clq");

    for (uint i=34; i < 50; i++) {
      for (uint k=100; k < 150; k++)
        std::cout << A->get(i, k) << " ";
      std::cout << std::endl;
    }

  }
  catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  
}
