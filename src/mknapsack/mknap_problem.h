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

  eoPop<Chrom> init_pop(uint length, double bias = 0.5);

  void operator()(Chrom &chromosome);

  /**
   * Verifica se um indivíduo/cromossomo quebra alguma das restrições do
   * problema. */
  bool break_constraint(const Chrom &chromosome);

  /**
   * Tornar uma solução inviável em uma solução viável */
  void repair_solution(Chrom &chromosome);

  std::vector<std::vector<float>> *weights();
  float optimal();
  std::vector<float>& capacities();
  std::vector<float>& profits();

private:
  uint m_num_capacities, m_num_items;
  float m_optimal;
  std::vector<float> m_capacities, m_profits;
  std::vector<std::vector<float>> m_weights;

  // Função para verifica se alguma restrição foi quebrada
  bool resources_is_greater(const std::vector<float>* resources);
};

#endif
