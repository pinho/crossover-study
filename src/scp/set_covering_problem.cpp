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
    os << "Shape da matriz: " << __matrix.num_rows() << "x"
            << __matrix.num_columns() << "\n";
    os << "Densidade da matriz: " << __matrix.density() << "\n";
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

bool SetCoveringProblem::check_coverage(const Chrom &chromosome) {
    auto coverageVec = this->coverage(chromosome);
    for (int &value : coverageVec)
        if (value == 0) return false;
    return true;
}

eoPop<Chrom> SetCoveringProblem::init_pop(uint length) {
    return Random<Chrom>::population(__chromSize, length);
}

F SetCoveringProblem::objective_function(Chrom &chromosome) {
    if (!check_coverage(chromosome))
        return 0;
    double sumOfCosts = 0.0;
    auto costs = __matrix.costs();
    for (uint i=0; i < __matrix.num_columns(); i++) {
        if (chromosome[i]) {
            sumOfCosts += costs[i];
        }
    }
    return double( 1.0/sumOfCosts );
}