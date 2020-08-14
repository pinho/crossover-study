#ifndef STEINERTREE_MINIMUM_SPANNING_TREE_H
#define STEINERTREE_MINIMUM_SPANNING_TREE_H

#include <iostream>
#include <vector>
#include <utility>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include "graph.h"

using edge_t = std::pair<int, int>;

// Kruskal algorithm returns the total cost of the edges selected in minimum spanning tree.
// Returns a pair where the first element is the set of edge which defines the spanning tree
// and the second element is the sum of the weights of these edges.
std::pair<std::vector<steiner::Edge>, float>
KruskalMST(unsigned int num_nodes, unsigned int num_edges, edge_t edges[], float weights[]);

#endif //STEINERTREE_MINIMUM_SPANNING_TREE_H
