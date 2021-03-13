#ifndef _CORE_DB_DATABASE_HPP
#define _CORE_DB_DATABASE_HPP

#include <sqlite/connection.hpp>
#include "base_model.hpp"

namespace db {

/**
 * @class Database
 * Gerencia a comunicação com um arquivo de banco de dados SQLite */
class Database {
public:

  Database(const char *filename)
  : db_filename(filename), db_conn(filename) {}

  ~Database() = default;

  /**
   * Retorna a instância conexão com o banco */
  const sqlite::connection& connection() {
    return this->db_conn;
  }

  /**
   * @brief Define o ponteiro para a tabela a ser usada pela instância do BD */
  void set_model(BaseModel *table_ptr) {
    this->tbModel = table_ptr;
  }

  /**
   * @brief Criar tabela. Usa a instância de table_controller
   * definida para inserir os dados na tabela */
  void create_table() {
    this->tbModel->create(&this->db_conn);
  }

  /**
   * @brief Insere os dados definidos na instância de BaseModel */
  void exec_insertion() {
    this->create_table();
    this->tbModel->insert(&this->db_conn);
  }

private:
  const char *db_filename;
  sqlite::connection db_conn;
  BaseModel *tbModel;
};

} // end of namespace db

#endif
