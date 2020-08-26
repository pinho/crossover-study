#include "set_covering_problem.h"

SetCoveringProblem::SetCoveringProblem(const char *filename) {
  this->__acronym = (char *) "SCP";
  this->__name    = (char *) "Set Covering Problem";
  this->__infilename = (char *) filename;
  this->__minimize = true;

  std::ifstream file(filename);
  if (file.is_open()) {
    this->coverage_matrix = new matrix(file);
    this->__chromSize = this->coverage_matrix->num_columns;
  } else {
    throw std::runtime_error("SCP input file not open");
  }
}


// Destrutor
SetCoveringProblem::~SetCoveringProblem() = default;

// Métodos herdados de "Problem"

void SetCoveringProblem::display_info(std::ostream& os) {
  os << this->__name << " (" << this->__acronym << ")\n";
  os << "Número de elementos no conjunto universo: " << num_elements << "\n";
  os << "Número de subconjuntos: " << num_subsets;
  os << std::endl;
}

eoPop<Chrom>
SetCoveringProblem::init_pop(unsigned int length, double bias = 0.5) {
  return Random<Chrom>::population(__chromSize, length, bias);
}

// Função Objetivo

SetCoveringProblem::Fitness
SetCoveringProblem::objective_function(Chrom& chrom) {
  return Fitness(0);
}
