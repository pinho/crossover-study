#ifndef _MWCP_H_
#define _MWCP_H_ 1

#include <numeric>
#include <limits>
#include <core/ga/problem.h>
#include <core/ga/random.h>
// #include "boolean_matrix.h"
#include "weighted_matrix.hpp"

class MWCProblem : public Problem {
public:
  MWCProblem(const char *filepath);
  ~MWCProblem();

  void display_info(std::ostream &os);
  eoPop<Chrom> init_pop(uint length, double bias = 0.5);
  double objective_function(Chrom &chrom);

  void repair_clique(Chrom& chrom);
  void expand_clique(Chrom& chrom, uint gene_index);

private:
  weighted_matrix mat; // matriz de adjacências
  std::vector<int> degrees; // vetor de graus
  // std::vector<int> *weights; // Vetor de pesos dos vértices
};

#endif