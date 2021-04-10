#include "mknap_model.h"

MknapModel::MknapModel() : db::BaseModel("mknap_executions") {}

MknapModel::MknapModel(CLI *cli) : db::BaseModel("mknap_executions") {
  this->crossover_id = cli->crossover_id;
  this->crossover_rate = cli->crossover_rate;
  this->crossover_name = CrossoverFabric::name(this->crossover_id);
  this->mutation_rate = cli->mutation_rate;
  this->stop_criteria = cli->stop_criteria;
  this->population_size = cli->pop_size;
}

void MknapModel::create(sqlite::connection *con) {
  std::string query;
  query = "CREATE TABLE IF NOT EXISTS "+ std::string(this->table_name) + " (";
  query += "id INTEGER PRIMARY KEY AUTOINCREMENT, "; 
  query += "population_size INTEGER, ";
  query += "stop_criteria INTEGER, ";
  query += "crossover INTEGER, ";
  query += "crossover_name TEXT, ";
  query += "crossover_rate REAL, ";
  query += "mutation_rate REAL, ";
  query += "instance_file TEXT, ";
  query += "convergence TEXT, ";
  query += "duration_in_ms REAL, ";
  query += "num_items INTEGER, ";
  query += "solution TEXT, ";
  query += "total_costs REAL);";

# ifdef NDEBUG
  std::cout << "Executando Query no banco:\n";
  std::cout << sql << std::endl;
# endif

  sqlite::execute(*con, query, true);
}

void MknapModel::insert(sqlite::connection *con) {
  std::string sql;
  sql = "INSERT INTO " + std::string(this->table_name) + " (";
  sql += "population_size, stop_criteria, crossover, crossover_name, ";
  sql += "crossover_rate, mutation_rate, instance_file, convergence, ";
  sql += "duration_in_ms, num_items, solution, total_costs";
  sql += ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

# ifdef NDEBUG
  std::cout << "Executando Query no banco:\n";
  std::cout << sql << std::endl;
# endif

  sqlite::execute ins(*con, sql);
  ins % this->population_size % this->stop_criteria   % this->crossover_id
      % this->crossover_name  % this->crossover_rate  % this->mutation_rate
      % this->instance_file   % this->convergence     % this->duration_in_ms
      % this->num_items       % this->solution        % this->total_costs;
  ins();
}
