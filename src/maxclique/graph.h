//
// Created by ronaldd on 31/03/2020.
//

#ifndef CROSSOVERCOMPARATOR_CLIQUE_GRAPH_H
#define CROSSOVERCOMPARATOR_CLIQUE_GRAPH_H

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_traits.hpp>


// Implementation of weighted node data
struct node_data {
    std::string id;
    float weight;
};

/*
 * Graph definition using Boost Graph Lib
 * Such as the graph should've weights on vertices
 * this definition uses the Node struct defined above
 */
using Graph = boost::adjacency_matrix<boost::undirectedS, uint>;
using Node  = boost::graph_traits<Graph>::vertex_descriptor;
using Edge  = boost::graph_traits<Graph>::edge_descriptor;
// Iterators
using NodeIterator = boost::graph_traits<Graph>::vertex_iterator;
using EdgeIterator = boost::graph_traits<Graph>::edge_iterator;


#endif //CROSSOVERCOMPARATOR_CLIQUE_GRAPH_H
