//
// Created by ronaldd on 26/04/2020.
//
#include "set_covering_problem.h"

using F = SetCoveringProblem::Fitness;

SetCoveringProblem::SetCoveringProblem(const char *filename) {
    this->__infilename = (char *) filename;
    this->__acronym = (char *) "SCP";
    this->__name = (char *) "Set Covering Problem";
    scpxx::SCPFile scpfile_(this->__infilename);
    scpfile_.bufferize();
    this->__matrix = scpfile_.generate_matrix();
    this->__chromSize = this->__matrix.num_columns();
}

const scpxx::Matrix& SetCoveringProblem::get_matrix() {
    return this->__matrix;
}

void SetCoveringProblem::display_info(std::ostream& os) {
    os << '[' << this->__acronym << "] " << this->__name << "\n";
    os << "Arquivo: " << __infilename << "\n";
    os << "Shape da matriz: " << __matrix.num_rows() << "x"
            << __matrix.num_columns() << "\n";
    os << "Tamanho de cromossomos: " << __chromSize << " genes.";
    os << std::endl;
}

std::vector<int> SetCoveringProblem::coverage(const Chrom &chromosome) {
    std::vector<int> result(__matrix.num_rows(), 0);
    int i = 0;
    for (auto row = __matrix.begin(); row != __matrix.end(); ++row) {
        for (uint j=0; j < __matrix.num_columns(); j++) {
            if (chromosome[j] and row->at(j)) {
                result[i] += (int) row->at(j);
            }
        }
        i++;
    }
    return result;
}

eoPop<Chrom> SetCoveringProblem::init_pop(uint length) {
    return Random<Chrom>::population(__chromSize, length);
}

F SetCoveringProblem::objective_function(Chrom &chromosome) {
    // Vericar cobertura
    auto vec = this->coverage(chromosome);
    bool coverall = std::all_of(vec.begin(), vec.end(), [](int item) {
        return item > 0;
    });

    if (coverall) {
        auto costs = this->__matrix.costs();
        double sum_ = 0.0;
        for (uint i=0; i < this->__chromSize; i++) {
            if (chromosome[i])
                sum_ += costs[i];
        }
        return F(1.0/sum_);
    }

    return F(0);
}