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
    this->weights = this->coverage_matrix->get_weights_pointer();
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

float* SetCoveringProblem::get_weights() {
  return this->coverage_matrix->get_weights_pointer();
}

void SetCoveringProblem::display_info(std::ostream& os) {
  os << this->__name << " (" << this->__acronym << ")\n";
  os << "Número de elementos no conjunto universo: " << this->num_elements << "\n";
  os << "Número de subconjuntos: " << this->num_subsets;
  os << std::endl;
}

/**
 * Versão 1 do método de inicialização de população:
 * Todos os cromossomos da população são inicializados com a mesma taxa de
 * alelos "1", definida pelo param "bias" */
// eoPop<Chrom>
// SetCoveringProblem::init_pop(unsigned int length, double bias) {
//   return Random<Chrom>::population(__chromSize, length, bias);
// }

/**
 * Versão 2 do método de inicialização de população:
 * A população é inicializada com diferentes probabilidades de geração de
 * alelos "1", para cada crossomo é usada uma probabilidade diferente que é
 * gerada aleatoriamente entre o "bias" passado e 0.5 (um valor padrão). */
eoPop<Chrom>
SetCoveringProblem::init_pop(unsigned int length, double bias) {
  eoPop<Chrom> aux_pop;
  unsigned int i = 1;
  do {
    Chrom generated;
    eoBooleanGenerator bitRng(Random<Chrom>::uniform(bias, 0.500001));
    eoInitFixedLength<Chrom> init(this->__chromSize, bitRng);
    init(generated);
    aux_pop.push_back(generated);
  } while (i++ < length);

  return aux_pop;
}


bool SetCoveringProblem::atend_constraint(const Chrom& chrom) {
  // Conta quantas colunas cobrem cada linha
  std::vector<int> coverVec(this->num_elements, 0);

  for (size_t row = 0; row < this->num_elements; row++) {
    for (size_t col = 0; col < this->num_subsets; col++) {
      if (chrom[col]) {
        coverVec[row] += (int) this->coverage_matrix->get(row, col);
      }
    }
    if (coverVec[row] == 0) {
      return false;
    }
  }
  return true;
}


// Função objetivo da cobertura de conjuntos
SetCoveringProblem::Fitness SetCoveringProblem::objective_function(Chrom& chrom)
{
  // Verifica se alguma linha tem contagem = zero
  if (!this->atend_constraint(chrom)) {
    return Fitness(0);
  }

  // Somar os custos das colunas selecionadas
  float accum = 0;
  for (size_t i = 0; i < __chromSize; i++) {
    if (chrom[i]) {
      accum += this->weights[i];
    }
  }

  return (Fitness) (1/accum);
}
