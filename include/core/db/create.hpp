#ifndef CORE_CREATE_DB_HPP_
#define CORE_CREATE_DB_HPP_

#include <string>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
using namespace sqlite;

#include "../cli/options.h"
#include "modes.hpp"

connection* db_create(std::string filename, db_structure dbmode) {
  sqlite::connection *con = new connection(filename);
  std::string query;

  if (dbmode == db_structure::mc) {
    // Contrói a tabel com estrutura para o problema do clique máximo
    query = "CREATE TABLE IF NOT EXISTS execucoes_mc (";
    query += "id INTEGER PRIMARY KEY AUTOINCREMENT, "; 
    query += "pop_length INTEGER, ";
    query += "num_gen INTEGER, ";
    query += "cross_rate REAL, ";
    query += "mutation_rate REAL, ";
    query += "crossover TEXT, ";
    query += "instance_file TEXT, ";
    query += "solution_size INTEGER, ";
    query += "solution TEXT, ";
    query += "convergence TEXT, ";
    query += "duration_ms REAL";
    query += ");";
    execute(*con, query, true);
  }
  
  else if (dbmode == db_structure::mk) {
    // Contrói a tabela com estrutura pro problema da mochila multidimensional
    query = "CREATE TABLE IF NOT EXISTS execucoes_mknap (";
    query += "id INTEGER PRIMARY KEY AUTOINCREMENT, "; 
    query += "pop_length INTEGER, ";
    query += "num_gen INTEGER, ";
    query += "cross_rate REAL, ";
    query += "mutation_rate REAL, ";
    query += "crossover TEXT, ";
    query += "instance_file TEXT, ";
    query += "item_indices TEXT, ";
    query += "total_costs REAL, ";
    query += "convergence TEXT, ";
    query += "duration_ms REAL";
    query += ");";
    execute(*con, query, true);
  }

  return con;
}

#endif