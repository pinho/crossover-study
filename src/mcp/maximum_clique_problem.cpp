#include "maximum_clique_problem.h"

// Util functions

bool is_connected(int indexU, int indexV, const Graph *graph) {
    Node u = *boost::vertices(*graph).first + indexU;
    Node v = *boost::vertices(*graph).first + indexV;
    return boost::edge(u, v, *graph).second;
}


template <typename T>
bool all_equals(std::vector<T>& vec, T value) {
    for (T& b : vec) {
        if (b != value) {
            return false;
        }
    }
    return true;
}


void count_adjacency(std::vector<std::pair<int, int>>& nodes, const Graph *graph_) {
    // count the number of adjacencies of each node
    for (auto&& [v, c] : nodes) {
        c = 0;
        for (auto&& [u, c2] : nodes) {
            if (v != u and is_connected(v, u, graph_)) {
                c++;
            }
        }
    }
}


bool check_counting(std::vector<std::pair<int, int>>& nodes) {
    for (auto& p : nodes) {
        int max = (int) nodes.size()-1;
        if (p.second != max) return false;
    }
    return true;
}


// Class scope

MaximumCliqueProblem::MaximumCliqueProblem (const char *filename) {
    try {
        this->__acronym = (char *) "MCP";
        this->__name = (char *) "Max Clique Problem";
        this->__infilename = (char *) filename;
        this->__minimize = true;
        std::vector<std::string> vecString = DimacsReader::read_elements(__infilename);

        // set attributes
        __numNodes = stoi(vecString[2]);
        __numEdges = stoi(vecString[3]);
        __graph = new Graph(__numNodes);
        NodeIterator vi, vi_end;
        boost::tie(vi, vi_end) = boost::vertices(*__graph);

        // set nodes and edges
        std::size_t index = 4;
        for (; index < vecString.size(); index+=3) {
            // set node when first char is 'n'
            // if (vecString[index] == "n") {
            //     __nodes.emplace_back()
            // }
            // set edge when first char is 'e'
            if (vecString[index] == "e") {
                int u = stoi(vecString[index+1])-1;
                int v = stoi(vecString[index+2])-1;
                // std::cout << "Adicionando edge(" << u << ", " << v << ")\n";
                boost::add_edge(u, v, *__graph);
            }
        }
        // number of genes is the number of nodes
        __chromSize = boost::num_vertices(*__graph);

    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


Graph *MaximumCliqueProblem::get_graph() {
    return this->__graph;
}


void MaximumCliqueProblem::display_info(std::ostream &os) {
    os << "[" << __acronym << "] " << __name << "\n";
    os << "  Número de vértices: " << boost::num_vertices(*__graph) << "\n";
    os << "  Número de arestas: " << boost::num_edges(*__graph) << "\n";
    os << "  Tamanho de cromossomo: " << __chromSize << "\n";
}


eoPop<Chrom> MaximumCliqueProblem::init_pop(uint length) {
    return Random<Chrom>::population(__chromSize, length);
}


void MaximumCliqueProblem::repair_clique(Chrom& chromosome) {
    assert(chromosome.size() == this->__chromSize);

    // create a vector with the nodes that is in solution
    std::vector<std::pair<int, int>> nodes_included;
    for (uint i=0; i < __chromSize; i++)
        if (chromosome[i]) nodes_included.emplace_back(i, 0);

    count_adjacency(nodes_included, __graph);
    bool cont = !check_counting(nodes_included);

    while (cont) {
        // sorting
        std::sort(nodes_included.begin(), nodes_included.end(),
                [](const auto &a, const auto &b) {
                    return a.second < b.second;
                }
        );
        // eliminate the minor
        chromosome[nodes_included.begin()->first] = 0;
        nodes_included.erase( nodes_included.begin() );
        // re-counting
        count_adjacency(nodes_included, __graph);
        // re-check
        cont = !check_counting(nodes_included);
    }
}


void MaximumCliqueProblem::expand_clique(eoBit<double>& chromosome_,
        unsigned int geneIndex_) {
    assert(geneIndex_ < chromosome_.size());
    NodeIterator vi, vi_end;
    boost::tie(vi, vi_end) = boost::vertices(*this->__graph);

    // Vertices indices in the solution
    std::vector<int> included, excluded;
    for (uint64_t i=0; i < chromosome_.size(); i++) {
        if (chromosome_[i]) {
            included.push_back(i);
        } else {
            excluded.push_back(i);
        }
    }

    for (int v : excluded) {
        bool add = true;
        for (int u : included) {
            if (!is_connected(v, u, this->__graph)) {
                add = false;
                break;
            }
        }
        if (add) {
            chromosome_[v] = 1; // add this node in chromosome
            included.push_back(v); // add on the included vector
        }
    }
}

MaximumCliqueProblem::Fitness
MaximumCliqueProblem::objective_function(Chrom& chromosome) {
    assert(chromosome.size() == this->__chromSize);

    repair_clique(chromosome);
    expand_clique(chromosome, 0);

    // FIXME: FO está somando a quantidade de vértices na solução
    Fitness sum = 0;
    for (uint index = 0; index < __chromSize; index++) {
        if (chromosome[index]) {
            sum += 1;
        }
    }
    return sum;
}