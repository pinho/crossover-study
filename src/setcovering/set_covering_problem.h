#ifndef CROSSOVERSTUDY_SET_COVERING_PROBLEM_H
#define CROSSOVERSTUDY_SET_COVERING_PROBLEM_H

#include <vector>
#include <set>
#include <cstdio>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <core/ga/problem.h>
#include <core/ga/random.h>
#include <core/utils/split.h>
#include <core/utils/vectors.h>
#include "scp_matrix.h"

#define LOG_DBG(message) std::cout << "[" << __func__ << "] " << message << std::endl


/**
 * Classe para o Problema da Cobertura de Conjuntos
 */
class SetCoveringProblem : public Problem {
public:
  // Construtor pardão
  SetCoveringProblem(const char* filename);

  // Destrutor padrão
  ~SetCoveringProblem();

  // Métodos virtuais herdados da class Problem

  void display_info(std::ostream &os);
  eoPop<Chrom> init_pop(uint length, double bias = 0.5);
  Fitness objective_function(Chrom &chromosome);

  // Verifica se um cromossomo atende às restrições da instância do problema
  bool atend_constraint(const Chrom& chrom);

  // Torna um indívíduo/cromossomo viável quando aplicado em cromossomo
  // que define uma solução que não respeita às restrições do problema 
  void make_feasible(Chrom& chrom);

  // Gera um novo incivíduo
  Chrom generate_individual();

  // Métodos relacionados à manipulação da matriz
  /** Retorna um ponteiro para a matriz booleana */
  matrix* get_matrix();
  /** Retorna um ponteiro para o array de pesos das colunas */
  float* get_weights();

private:
  size_t num_elements; // Número de linhas na matriz
  size_t num_subsets; // Número de colunas na matriz
  matrix *coverage_matrix; // Matriz de cobertura
  float *weights; // Pesos das colunas
  std::vector< std::set<unsigned int> > columns_that_covers; // Colunas que cobrem cada linha
  std::vector< std::set<unsigned int> > rows_covered_by; // Linhas sendo cobertas para cada coluna
  std::set<unsigned int> all_elements; // Conjunto de todas os elementos (linhas)

  /**
   * Retorna um conjunto (set) de linhas que estão sendo cobertas pela solução
   * definida por um determinado cromossomo */
  std::set<unsigned int> coverage_set(const Chrom &chrom);
};

#endif