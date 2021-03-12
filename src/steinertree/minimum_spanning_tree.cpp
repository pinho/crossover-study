#include "minimum_spanning_tree.h"

std::pair<std::vector<steiner::Edge>, float>
KruskalMST(unsigned int num_nodes, unsigned int num_edges, edge_t edges[], float weights[]) {
  using namespace boost;
  using steiner::Graph;
  using steiner::Edge;

  Graph g(edges, edges + num_edges, weights, num_nodes);
  property_map<Graph, edge_weight_t>::type weightof = get(edge_weight, g);
  std::vector<Edge> spanning_tree;

  kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
  float total_weight = 0;

  for (auto edge : spanning_tree) {
    total_weight += weightof(edge);
  }

  return std::pair<std::vector<Edge>, float>(spanning_tree, total_weight);
}
