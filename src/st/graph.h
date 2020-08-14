//-----------------------
// USANDO BOOST LIBS
//-----------------------

#ifndef CROSSOVERCOMPARATOR_STEINER_GRAPH_H
#define CROSSOVERCOMPARATOR_STEINER_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

// Definition of Graph as undirected and using vector for containers
namespace steiner {
    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
    boost::no_property, boost::property<boost::edge_weight_t, float> >;
    using Node = boost::graph_traits<Graph>::vertex_descriptor;
    using Edge = boost::graph_traits<Graph>::edge_descriptor;
}

#endif //CROSSOVERCOMPARATOR_STEINER_GRAPH_H