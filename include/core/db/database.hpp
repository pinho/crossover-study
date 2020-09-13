#ifndef _CORE_DB_DATABASE_HPP
#define _CORE_DB_DATABASE_HPP

#include <sqlite/connection.hpp>
#include "database_strategy.hpp"

/**
 * @class Database
 * Gerencia a comunicação com um arquivo de banco de dados SQLite */

class Database {
public:

  Database(const char *filename) : db_filename(filename), db_conn(filename) {}

  ~Database() {}

  void insert() {
    this->db_strategy->create_table(&db_conn);
    this->db_strategy->insert_data(&db_conn);
  }

  const DatabaseStrategy::Connection* connection() {
    return &this->db_conn;
  }

  void set_strategy(DatabaseStrategy &strategy) {
    this->db_strategy = &strategy;
  }

private:
  const char *db_filename;
  sqlite::connection db_conn;
  DatabaseStrategy *db_strategy;
};

#endif