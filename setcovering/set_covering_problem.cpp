//
// Created by ronaldd on 26/04/2020.
//

#include "set_covering_problem.h"

using F = SetCoveringProblem::Fitness;

SetCoveringProblem::SetCoveringProblem(const char *filename) {
    this->__infilename = (char *) filename;
    this->__acronym = "SCP";
    this->__name = "Set Covering Problem";
    scpxx::SCPFile scpfile_(this->__infilename);
    scpfile_.bufferize();
    this->__matrix = scpfile_.generate_matrix();
    this->__chromSize = this->__matrix.num_columns();
}

SetCoveringProblem::~SetCoveringProblem() = default;

auto SetCoveringProblem::get_matrix() -> const scpxx::Matrix& {
    return this->__matrix;
}

void SetCoveringProblem::display_info(std::ostream& os) {
    os << this->__acronym << " - " << this->__name << "\n";
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

F SetCoveringProblem::objective_function(Chrom &chromosome) {
    std::cout << chromosome << std::endl;
    return F();
}