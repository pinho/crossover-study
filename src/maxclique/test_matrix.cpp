#include <iostream>
#include <algorithm>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/graph/graphviz.hpp>

using Graph = boost::adjacency_matrix<boost::undirectedS, uint>;
using Node = boost::graph_traits<Graph>::vertex_descriptor;
using Edge = boost::graph_traits<Graph>::edge_descriptor;
using Node_it = boost::graph_traits<Graph>::vertex_iterator;

int main() {
    Graph graph(20);

    Node_it ni, ni_end;
    boost::tie(ni, ni_end) = boost::vertices(graph);

    boost::add_edge(2, 6, graph);
    boost::add_edge(12, 16, graph);
    boost::add_edge(1, 5, graph);
    boost::add_edge(3, 8, graph);
    boost::add_edge(11, 15, graph);

    for (; ni != ni_end; ++ni) {
        std::cout << *ni << "\t";
        for (uint i = 0; i < 20; i++) {
            auto e = boost::edge(*ni, i, graph);
            std::cout << e.second << " ";
        }
        std::cout << "\n";
    }

    std::cout << graph[0] << " ";
    std::cout << graph[12] << " ";
    std::cout << graph[10] << " ";
    std::cout << graph[9] << " ";
    std::cout << graph[4] << " \n";

    return 0;
}