#ifndef _MCP_H_
#define _MCP_H_

#include <core/ga/problem.h>

#include "boolean_matrix.h"

class MCProblem : public Problem {
public:
  MCProblem(const char *filepath);
  ~MCProblem();

  void display_info(std::ostream &os);
  eoPop<Chrom> init_pop(uint length);
  Fitness objective_function(Chrom &chromosome);

private:
  static matrix *M;
};

#endif