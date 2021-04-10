#ifndef _MWCP_H_
#define _MWCP_H_ 1

#include <numeric>
#include <limits>
#include <core/ga/problem.h>
#include <core/ga/random.h>
#include "weighted_matrix.hpp"

class MWCProblem : public Problem {
public:
  using Problem::Fitness;

  MWCProblem(const char *filepath);
  ~MWCProblem();

  eoPop<Chrom> init_pop(uint length, double bias = 0.5);

  void operator()(Chrom &chrom);

  void repair_clique(Chrom& chrom);
  void expand_clique(Chrom& chrom, uint gene_index);

private:
  weighted_matrix mat; // matriz de adjacências
  std::vector<int> degrees; // vetor de graus
};

#endif
