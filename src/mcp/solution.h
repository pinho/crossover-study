#ifndef CROSSOVERRESEARCH_SOLUTION_H
#define CROSSOVERRESEARCH_SOLUTION_H

#include <vector>
#include <ga/encoding.h>

namespace mcp {

    struct solution_t {
        uint num_nodes;
        std::vector<uint> nodes;

        explicit solution_t(const Chrom& chrom);

        // friend std::ostream& operator<< (std::ostream &os, solution_t &s);
    };

}

mcp::solution_t::solution_t(const Chrom& chrom) {
    if (!chrom.invalid())
        this->num_nodes = (uint) chrom.fitness();

    for (uint i=0; i < chrom.size(); i++) {
        if (chrom[i]) nodes.emplace_back(i);
    }
}

// std::ostream &operator<< (std::ostream &os, mcp::solution_t &s) {}

#endif