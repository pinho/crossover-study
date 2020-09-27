#ifndef _CORE_DB_DATABASE_HPP
#define _CORE_DB_DATABASE_HPP

#include <sqlite/connection.hpp>
#include "table_controller.hpp"

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
  void set_controller(TableController *table_ptr) {
    this->tbCtrl = table_ptr;
  }

  /**
   * @brief Criar tabela. Usa a instância de table_controller
   * definida para inserir os dados na tabela */
  void create_table() {
    this->tbCtrl->create(&this->db_conn);
  }

  /**
   * @brief Insere os dados definidos na instância de TableController */
  void insert_data() {
    this->create_table();
    this->tbCtrl->insert(&this->db_conn);
  }

private:
  const char *db_filename;
  sqlite::connection db_conn;
  TableController *tbCtrl;
};

#endif