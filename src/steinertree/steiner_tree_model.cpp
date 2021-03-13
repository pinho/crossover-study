#include "steiner_tree_model.h"

SteinerTreeModel::SteinerTreeModel()
: db::BaseModel("steiner_executions"), num_steiner_nodes(int()),
  steiner_nodes(std::string()), total_costs(float()) {}

SteinerTreeModel::SteinerTreeModel(CLI *cli)
: db::BaseModel("steiner_executions"), num_steiner_nodes(int()),
  steiner_nodes(std::string()), total_costs(float())
{
  this->crossover_id = cli->crossover_id;
  this->crossover_rate = cli->crossover_rate;
  this->crossover_name = CrossoverFabric::name(this->crossover_id);
  this->mutation_rate = cli->mutation_rate;
  this->num_generations = cli->epochs;
  this->population_size = cli->pop_size;
}

void SteinerTreeModel::set_solution_data(std::vector<int>& solutionNodes) {
  this->num_steiner_nodes = int(solutionNodes.size());
  this->steiner_nodes = db::BaseModel::sequence_to_string<int>(solutionNodes);
}

void SteinerTreeModel::create(sqlite::connection *con) {
  std::string sql;
  sql = "CREATE TABLE IF NOT EXISTS "+ std::string(this->table_name) + " (";
  sql += "id INTEGER PRIMARY KEY AUTOINCREMENT, "; 
  sql += "population_size INTEGER, ";
  sql += "num_generations INTEGER, ";
  sql += "crossover INTEGER, ";
  sql += "crossover_name TEXT, ";
  sql += "crossover_rate REAL, ";
  sql += "mutation_rate REAL, ";
  sql += "instance_file TEXT, ";
  sql += "convergence TEXT, ";
  sql += "duration_in_ms REAL, ";
  sql += "num_steiner_nodes INTEGER, ";
  sql += "steiner_nodes TEXT, ";
  sql += "total_costs REAL);";

# ifdef NDEBUG
  std::cout << "Executando Query no banco:\n";
  std::cout << sql << std::endl;
# endif
  sqlite::execute(*con, sql, true);
}

void SteinerTreeModel::insert(sqlite::connection *con) {
  std::string sql;
  sql = "INSERT INTO " + std::string(this->table_name) + " (";
  sql += "population_size, num_generations, crossover, crossover_name, ";
  sql += "crossover_rate, mutation_rate, instance_file, convergence, ";
  sql += "duration_in_ms, num_steiner_nodes, steiner_nodes, total_costs";
  sql += ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

# ifdef NDEBUG
  std::cout << "Executando Query no banco:\n";
  std::cout << sql << std::endl;
# endif

  sqlite::execute ins(*con, sql);
  ins % this->population_size   % this->num_generations % this->crossover_id
      % this->crossover_name    % this->crossover_rate  % this->mutation_rate
      % this->instance_file     % this->convergence     % this->duration_in_ms
      % this->num_steiner_nodes % this->steiner_nodes   % this->total_costs;
  ins();  
}
