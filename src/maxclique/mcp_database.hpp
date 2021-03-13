#ifndef MCP_DATABASE_HPP_
#define MCP_DATABASE_HPP_ 1

#include <core/db/base_model.hpp>
#include <core/cli/options.h>
#include <core/utils/trim_filename.h>
#include <core/ga/crossover_fabric.h>

/**
 * @struct MCPTable
 * Concentra os dados de armazenamento da tabela do porblema do clique máximo */
struct MCPModel : public db::BaseModel {
public:
  int solution_size;
  int total_cost;
  std::string solution;

  explicit MCPModel()
  : db::BaseModel("maxclique_executions"), solution_size(0), total_cost(0),
    solution(std::string()) {}

  MCPModel(CLI *cli);

  ~MCPModel();

  void create(sqlite::connection *con);

  void insert(sqlite::connection *con);
};

#endif
