#ifndef CORE_DB_BASE_MODEL_HPP_
#define CORE_DB_BASE_MODEL_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/database_exception.hpp>
#include "../ga/encoding.h"

namespace db {

/**
 * @struct BaseModel organiza os dados que devem ser armazenados em uma
 * tabela para uma execução.
 */
class BaseModel {
public:
  const char *table_name; // Nome da tabela

  // OBS: unsigned int não funciona diretamente com o operator% de sqlite::execute
  int population_size;        // Tamanho da população de indivíduos
  int stop_criteria;          // Número de gerações
  int crossover_id;           // ID do operador de crossover
  double crossover_rate;      // Taxa de cruzamento
  double mutation_rate;       // Taxa de mutação
  double duration_in_ms;      // Duração da evolução em milisegundos
  std::string crossover_name; // Nome do operador de crossover
  std::string convergence;    // Convergência da busca (texto com separador)
  std::string instance_file;  // Nome do arquivo de instancia usado

  BaseModel(const char *t_tablename)
  : table_name(t_tablename), population_size(0), stop_criteria(0),
    crossover_id(0), crossover_rate(0.0), mutation_rate(0.0),
    duration_in_ms(0.0), crossover_name(std::string()),
    convergence(std::string()) {}

  // Default destructor
  ~BaseModel() = default;

  /**
   * Converte um vector para uma string contendo todos os seus valores
   * separados por vírgula */
  template <typename T>
  static std::string sequence_to_string(std::vector<T>& seq) {
    std::stringstream ss;
    auto it = seq.cbegin();
    for (; it != seq.cend(); ++it) {
      ss << *it;
      if ( it != seq.cend()-1 ) ss << ',';
    }
    return ss.str();
  }

  // Define o atributo convergência a partir de uma sequência de cromossomos
  void set_convergence(const std::vector<Chrom>& convVec) {
    if (!this->convergence.empty()) {
      this->convergence.clear();
    }
    std::stringstream ss;
    for (auto it = convVec.cbegin(); it != convVec.cend(); ++it) {
      ss << it->fitness();
      if ( it != convVec.cend()-1 ) {
        ss << ',';
      }
    }
    this->convergence = ss.str();
  }

  // TODO: adicionar metodo de setar a duração

  // TODO: problema com o instance_file
  // Descobrir porque o instance_file tá sendo armazendado como BLOB no banco

  // Cria esturtura da tabela no banco de dados
  virtual void create(sqlite::connection *con) = 0;

  // Inserir os dados de (*this) no banco de dados
  virtual void insert(sqlite::connection *con) = 0;
};

} // endof namespace db

#endif
