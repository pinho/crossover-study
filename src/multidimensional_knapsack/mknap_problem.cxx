#include "mknap_problem.h"

/**
 * Soma condicional
 * Retornar a soma do vector somente para os genes iguais a 1 no cromossomo
 */
float sum_by_genes(std::vector<float>::iterator _vecFirst,
                   std::vector<float>::iterator _vecLast,
                   Chrom::const_iterator _chromFirst,
                   Chrom::const_iterator _chromLast)
{
  float __sum = 0.0F;
  for (; _vecFirst != _vecLast; ++_vecFirst) {
    if (*_chromFirst) {
      __sum += *_vecFirst;
    }
    if (_chromFirst == _chromLast) {
      break;
    }
    ++_chromFirst;
  }
  return __sum;
}


// -------------------
// Métodos da classe
// -------------------

/**
 * Implementa a leitura do arquivo de instância deinifindo
 * todos os atributos membros
 */
MKnapsackProblem::MKnapsackProblem (const char *filename) {
  using std::vector;

  this->__acronym = (char *) "MKP";
  this->__name = (char *) "Problema da Mochila Muldimensional";
  this->__infilename = (char *) filename;
  this->__minimize = false;
  
  // scpxx::InstanceFile<float> f(filename);
  std::ifstream f(filename);
  
  if (f.is_open()) {
    // Pegando todo o conteúdo do arquivo
    std::string all_from_file(
      (std::istreambuf_iterator<char>(f)),
      (std::istreambuf_iterator<char>())
    );
    auto _string_values = split(all_from_file, ' ');
    auto _values = convert_vec(_string_values);
    
    this->m_num_items = (uint) _values[0];
    this->m_num_capacities = (uint) _values[1];
    this->m_optimal = _values[2];

    this->__chromSize = m_num_items;

    // Lendo os itens e seus valores
    m_profits = vector<float>(m_num_items);
    for (uint i=0; i < m_num_items; i++)
        m_profits[i] = _values[i+3];

    // Lendo valores das restrições
    m_weights = vector<vector<float>>(m_num_capacities, vector<float>(m_num_items));
    for (uint i=0; i < m_num_capacities; i++) {
      for (uint j=0; j < m_num_items; j++) {
        m_weights[i][j] = _values[ 3 + m_num_items + j + i*m_num_items ];
      }
    }
    int _i = 3 + m_num_items + m_num_items*m_num_capacities;
    m_capacities = vector<float>(m_num_capacities);
    for (uint i=0; i < m_num_capacities; i++) {
      m_capacities[i] = _values[_i]; _i++;
    }
  }
}


MKnapsackProblem::~MKnapsackProblem() = default;


eoPop<Chrom> MKnapsackProblem::init_pop(uint length, double bias) {
  eoPop<Chrom> _pop = Random<Chrom>::population(__chromSize, length, bias);
  for (Chrom& chr : _pop) {
    this->repair_solution(chr);
  }
  return _pop;
}


void MKnapsackProblem::display_info(std::ostream &os) {
  os << this->__name << " - " << (__minimize?"Minimização":"Maximização") <<std::endl;
  os << this->m_num_items << " items\n";
  os << "Profits: ";
  print_vec<float>(m_profits, os);
  os << this->m_num_capacities << " restrições\n";
  os << "Capacidades: ";
  print_vec<float>(m_capacities, os);
}


MKnapsackProblem::Fitness MKnapsackProblem::objective_function(Chrom& chromosome_) {
  assert(chromosome_.size() == m_num_items);
  // Check constraint
  if (break_constraint(chromosome_)) {
    return Fitness(0);
  }
  // Sum r_ij * x_j
  // Fitness _sum = Fitness(0);
  // for (uint i=0; i < m_num_items; i++) {
  //   if (chromosome_[i])
  //     _sum += m_profits[i];
  // }

  return sum_by_genes(m_profits.begin(), m_profits.end(),
      chromosome_.cbegin(), chromosome_.cend());
}


bool MKnapsackProblem::break_constraint(const Chrom& chromosome_) {
  try {
    std::vector<float> somas;
    // Calcular a soma de cada linha (pesos de um item) na matriz de pesos
    for (std::vector<float>& weights_of_item : m_weights) {
      somas.push_back(
        sum_by_genes(
          weights_of_item.begin(), weights_of_item.end(),
          chromosome_.cbegin(), chromosome_.cend()
        )
      );
    }
    for (std::size_t i=0; i < m_num_capacities; i++) {
      if (somas[i] > m_capacities[i]) {
        return true;
      }
    }
    return false;
  }
  catch (std::exception &e) {
    auto msg = std::string("break_constraint::") + e.what();
    throw std::runtime_error(msg);
  }
}

inline bool MKnapsackProblem::resources_is_greater(const std::vector<float>* resources)
{
  bool result = false;
  for (size_t i=0; i < resources->size(); i++) {
    if (resources->at(i) > this->m_capacities[i]) {
      result = true;
      break;
    }
  }
  return result;
}


void MKnapsackProblem::repair_solution(Chrom &chromosome) {
  assert(chromosome.size() == this->m_num_items);
  std::vector<float> accum_resources;

  for (size_t i=0; i < this->m_num_capacities; i++) {
    float resources_sum = 0.0f;
    for (size_t j=0; j < this->m_num_items; j++) {
      resources_sum += m_weights[i][j] * int(chromosome[j]);
    }
    accum_resources.push_back(resources_sum);
  }
  assert(accum_resources.size() == this->m_num_capacities);

  // Drop phase
  int capacity_idx = this->m_num_capacities;
  for (auto chrom_it = chromosome.rbegin(); chrom_it != chromosome.rend(); ++chrom_it)
  {
    if (*chrom_it && this->resources_is_greater(&accum_resources)) {
      *chrom_it = false;
      capacity_idx -= 1;
      for (size_t i=0; i < this->m_num_capacities; i++) {
        accum_resources[i] -= this->m_weights[i][capacity_idx];
      }
    }
  }

  // TODO: Adicionar a "ADD PHASE" (?)
}


std::vector< std::vector<float> > *MKnapsackProblem::weights() {
  return &this->m_weights;
}

float MKnapsackProblem::optimal() {
  return this->m_optimal;
}

std::vector<float>& MKnapsackProblem::profits() {
  return this->m_profits;
}

std::vector<float>& MKnapsackProblem::capacities() {
  return this->m_capacities;
}
