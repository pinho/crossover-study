#ifndef CROSSOVERRESEARCH_PROBLEM_FABRIC_H
#define CROSSOVERRESEARCH_PROBLEM_FABRIC_H

#include "scp/set_covering_problem.h"
#include "mkp/m_knapsack_problem.h"
#include "mcp/maximum_clique_problem.h"

/**
 * Classe estática que cria instâncias de problemas concretos
 */
class ProblemFabric {
public:
    static Problem *create(const char *filename, std::string problemName);
};

#endif