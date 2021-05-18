#include "mcp_database.hpp"

MCPModel::MCPModel(CLI *cli)
: db::BaseModel("maxclique_executions"), solution_size(0), total_cost(0),
  solution(std::string())
{
  this->population_size = cli->pop_size;
  this->stop_criteria = cli->stop_criteria;
  this->mutation_rate = cli->mutation_rate;
  this->crossover_rate = cli->crossover_rate;
  this->crossover_id = cli->crossover_id;
  this->crossover_name = CrossoverFabric::name(cli->crossover_id);
  const char *aux = trim_filename(cli->infile);
  this->instance_file = std::string(aux);
  this->solution_size = 0;
  this->solution = std::string();
}

MCPModel::~MCPModel() = default;

void MCPModel::create(sqlite::connection *con) {
  std::string query;
  query = "CREATE TABLE IF NOT EXISTS ";
  query += this->table_name;
  query += " (";
  query += "id INTEGER PRIMARY KEY AUTOINCREMENT, "; 
  query += "population_size INTEGER, ";
  query += "stop_criteria INTEGER, ";
  query += "mutation_rate REAL, ";
  query += "crossover_rate REAL, ";
  query += "crossover INTEGER, ";
  query += "crossover_name TEXT, ";
  query += "instance_file TEXT, ";
  query += "solution_size INTEGER, ";
  query += "solution TEXT, ";
  query += "total_costs TEXT, ";
  query += "convergence TEXT, ";
  query += "duration_in_ms REAL";
  query += ");";
  sqlite::execute(*con, query, true);
}

void MCPModel::insert(sqlite::connection *con) {
  std::string sql;
  sql = "INSERT INTO " + std::string(this->table_name) + " (";
  sql += "population_size, stop_criteria, crossover, crossover_name, ";
  sql += "crossover_rate, mutation_rate, instance_file, convergence, ";
  sql += "duration_in_ms, solution_size, solution, total_cost";
  sql += ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

  sqlite::execute ins(*con, sql);
  ins % this->population_size % this->stop_criteria   % this->crossover_id
      % this->crossover_name  % this->crossover_rate  % this->mutation_rate
      % this->instance_file   % this->convergence     % this->duration_in_ms 
      % this->solution_size   % this->solution        % this->total_cost;
  ins();
}
