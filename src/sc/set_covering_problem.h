#ifndef CROSSOVERSTUDY_SET_COVERING_PROBLEM_H
#define CROSSOVERSTUDY_SET_COVERING_PROBLEM_H

#include <vector>
#include <cstdio>
#include <fstream>
#include <core/ga/problem.h>
#include <core/ga/random.h>
#include <core/utils/split.h>
#include <core/utils/vectors.h>
// #include "subset.h"
#include "scp_matrix.h"

/**
 * Classe para o Problema da Cobertura de Conjuntos
 */
class SetCoveringProblem : public Problem {
public:
  // Construtor pardão
  SetCoveringProblem(const char* filename);

  // Destrutor padrão
  ~SetCoveringProblem();

  void display_info(std::ostream &os);
  eoPop<Chrom> init_pop(uint length, double bias);
  Fitness objective_function(Chrom &chromosome);

  // Métodos relacionados à manipulação da matriz
  matrix* get_matrix();

private:
  size_t num_elements; // Número de linhas na matriz
  size_t num_subsets; // Número de colunas na matriz
  matrix *coverage_matrix; // Matriz de cobertura
};

#endif