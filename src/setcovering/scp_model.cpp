#include "scp_model.h"

SCPModel::SCPModel()
: db::BaseModel("setcovering_executions"), num_columns(0),
  columns(std::string()), total_costs(0.0f) {}

SCPModel::SCPModel(CLI *cli)
: db::BaseModel("setcovering_executions"), num_columns(0), 
  columns(std::string()), total_costs(0.0f)
{
  this->crossover_id = cli->crossover_id;
  this->crossover_rate = cli->crossover_rate;
  this->crossover_name = CrossoverFabric::name(this->crossover_id);
  this->mutation_rate = cli->mutation_rate;
  this->stop_criteria = cli->stop_criteria;
  this->population_size = cli->pop_size;
}

void SCPModel::create(sqlite::connection *con) {
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
  query += "num_columns INTEGER, ";
  query += "columns TEXT, ";
  query += "total_costs REAL);";

# ifdef NDEBUG
  std::cout << "Executando Query no banco:\n";
  std::cout << query << std::endl;
# endif
  sqlite::execute(*con, query, true);
}

void SCPModel::insert(sqlite::connection *con) {
  std::string sql;
  sql = "INSERT INTO " + std::string(this->table_name) + " (";
  sql += "population_size, stop_criteria, crossover, crossover_name, ";
  sql += "crossover_rate, mutation_rate, instance_file, convergence, ";
  sql += "duration_in_ms, num_columns, columns, total_costs";
  sql += ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

# ifdef NDEBUG
  std::cout << "Executando Query no banco:\n";
  std::cout << sql << std::endl;
# endif

  sqlite::execute ins(*con, sql);
  ins % this->population_size % this->stop_criteria   % this->crossover_id
      % this->crossover_name  % this->crossover_rate  % this->mutation_rate
      % this->instance_file   % this->convergence     % this->duration_in_ms
      % this->num_columns     % this->columns         % this->total_costs;
  ins();
}
