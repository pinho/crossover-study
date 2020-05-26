//
// Created by pinho on 5/1/20.
//

#ifndef CROSSOVERRESEARCH_MAXIMUM_CLIQUE_PROBLEM_H
#define CROSSOVERRESEARCH_MAXIMUM_CLIQUE_PROBLEM_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <ga/problem.h>
#include <ga/random.h>
#include <io/dimacs_reader.h>

#include "graph.h"

/*
 * Check if two nodes is connected in a graph
 */
bool is_connected(int indexU, int indexV, const Graph* graph);


/*
 * Check if all elements in a vector are equals to a 'value'
 */
bool all_equals(std::vector<bool>& vec, bool value);


/*
 * Class for the Maximum Clique Problem
 * Formulation based on Rebecca Moussa's paper (2019)
 */
class MaximumCliqueProblem : public Problem {
public:
    using Fitness = Problem::Fitness;

    /*
     * Default constructor
     * Get an instance file from DIMACS
     */
    MaximumCliqueProblem(const char *filename);

    ~MaximumCliqueProblem() = default;

    void display_info(std::ostream& os) override;

    eoPop<Chrom> init_pop(uint length) override;

    /**
     * Objective function:
     * 
     * Use repair clique and expand clique algorithm (Moussa 2019) */
    Fitness objective_function(Chrom& chromosome) override;

    /*
     * Return a reference to the graph object
     */
    Graph* get_graph();

    /**
     * Try to repair a chromosome removing genes of vertices that not are all-paired
     */
    void repair_clique(Chrom& chromosome);

    /* ExpandClique
     *
     * The ExpandClique is an operator that aims at deterministically expanding the
     * size of the clique that was found so far. The operator selects a random vertex
     * Vk and iterates over the randomly sets gene i to 1 if the corresponding vertex
     * Vi is genes from vertices k+1 till n. At each iteration, the operator pairwise
     * connected to all vertices in the current clique. The final outcome is a larger
     * clique. [Rebecca Moussa et. al 2019]
     */
    void expand_clique(Chrom& chromosome, unsigned int geneIndex);


protected:
    uint __numNodes, __numEdges;
    std::vector<node_data> __nodes;
    Graph *__graph;
};

#endif //CROSSOVERCOMPARATOR_MAXIMUM_CLIQUE_PROBLEM_H
