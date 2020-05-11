//
// Created by ronaldd on 29/04/2020.
//

#ifndef CROSSOVERRESEARCH_SOLUTION_H
#define CROSSOVERRESEARCH_SOLUTION_H

#include <algorithm>
#include <ga/encoding.h>

struct solution_t {
    float cost;
    uint num_columns;
    // Default constructor
    explicit solution_t() = default;
    // Constructor through chromosome decoding
    explicit solution_t(const Chrom& chrom);
    // Output Stream operator
    friend std::ostream& operator <<(std::ostream& os, const solution_t& sol);
};

solution_t::solution_t(const Chrom& chrom) {
    this->cost = (float) (1.0F / chrom.fitness());
    this->num_columns = (uint) std::accumulate(chrom.begin(), chrom.end(), 0);
}

std::ostream& operator<<(std::ostream &os, const solution_t &sol) {
    os << "[ custo = " << sol.cost;
    if (sol.num_columns > 0)
        os << "; " << sol.num_columns << " colunas";
    os << " ]";
    return os;
}

#endif //CROSSOVERRESEARCH_SOLUTION_H
