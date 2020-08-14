#ifndef STEINER_TREE_PROBLEM_H
#define STEINER_TREE_PROBLEM_H

#include <fstream>
#include <string>
#include <core/utils/split.h>
#include <core/utils/vectors.h>
#include <core/ga/problem.h>
#include <core/ga/random.h>
#include "minimum_spanning_tree.h"

class SteinerTreeProblem : public Problem {
public:
  SteinerTreeProblem(const char* filename);
  ~SteinerTreeProblem();

  void display_info(std::ostream& os);
  eoPop<Chrom> init_pop(uint len, double _bias = 0.5);
  Fitness objective_function(Chrom& chromosome);

  // Remover todas as arestas adjacentes a um conjunto de vértices
  void remove_node(std::vector<edge_t>& edges, std::vector<float>& weights, int node);

private:
  uint num_nodes, // Número de vértices
       num_edges, // Número de arestas
       num_steiner_nodes; // Número de vértices de Steiner
  std::vector<int> *nodes_vec_ptr, // Ponteiro para vector de vértices
                   *steiner_nodes_vec_ptr; // Ponteiro para vector de vértices de Steiner
  std::vector<float> *weights_vec_ptr; // Ponteiro para vector de pesos das arestas
  std::vector<edge_t> *edges_vec_ptr; // Ponteiro para vector de pares de inteiros (arestas)
};

#endif
