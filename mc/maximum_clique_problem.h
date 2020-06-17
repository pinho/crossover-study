#ifndef _MCP_H_
#define _MCP_H_

#include <numeric>
#include <limits>
#include <core/ga/problem.h>
#include <core/ga/random.h>

#include "boolean_matrix.h"

class MCProblem : public Problem {
public:
  MCProblem(const char *filepath);
  ~MCProblem();

  void display_info(std::ostream &os);
  eoPop<Chrom> init_pop(uint length, double bias = 0.5);
  double objective_function(Chrom &chrom);

  void repair_clique(Chrom& chrom);
  void expand_clique(Chrom& chrom, uint gene_index);

private:
  matrix M; // matriz de adjacências
  std::vector<int> degrees; // vetor de graus
};

#endif