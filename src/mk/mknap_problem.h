#ifndef _MULTI_KNAP_PROBLEM_H_
#define _MULTI_KNAP_PROBLEM_H_

#include <vector>
#include <string>
#include <core/ga/problem.h>
#include <core/ga/random.h>
#include <core/utils/split.h>
#include <core/utils/vectors.h>
// #include <scpxx/InstanceFile.h>

class MKnapsackProblem : public Problem {
public:
  using Problem::Fitness;

  MKnapsackProblem(const char *);
  ~MKnapsackProblem();

  void display_info(std::ostream &os);

  eoPop<Chrom> init_pop(uint length, double bias = 0.5);

  Fitness objective_function(Chrom &chromosome);

  bool break_constraint(const Chrom &chromosome);

  std::vector<std::vector<float>> *weights();
  float optimal();
  std::vector<float>& capacities();
  std::vector<float>& profits();

private:
  uint m_num_capacities, m_num_items;
  float m_optimal;
  std::vector<float> m_capacities, m_profits;
  std::vector<std::vector<float>> m_weights;
};

#endif