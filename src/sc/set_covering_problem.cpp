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
    this->num_subsets = this->coverage_matrix->num_columns;
    this->num_elements = this->coverage_matrix->num_rows;
  } else {
    std::cerr << "Use a opção -f" << std::endl;
    throw std::runtime_error(
      "Não foi possível abrir o arquivo no caminho: "+ std::string(filename)
    );
  }
}

// Destrutor
SetCoveringProblem::~SetCoveringProblem() = default;

// Métodos herdados de "Problem"

matrix* SetCoveringProblem::get_matrix() {
  return this->coverage_matrix;
}

void SetCoveringProblem::display_info(std::ostream& os) {
  os << this->__name << " (" << this->__acronym << ")\n";
  os << "Número de elementos no conjunto universo: " << this->num_elements << "\n";
  os << "Número de subconjuntos: " << this->num_subsets;
  os << std::endl;
}

eoPop<Chrom>
SetCoveringProblem::init_pop(unsigned int length, double bias = 0.5) {
  return Random<Chrom>::population(__chromSize, length, bias);
}

// Função Objetivo

SetCoveringProblem::Fitness
SetCoveringProblem::objective_function(Chrom& chrom) {
  // TODO: Função objetivo da cobertura de conjuntos
  return Fitness(0);
}
