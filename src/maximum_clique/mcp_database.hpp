#ifndef MCP_DATABASE_HPP_
#define MCP_DATABASE_HPP_ 1

#include <core/db/table_controller.hpp>
#include <core/cli/options.h>
#include <core/utils/trim_filename.h>
#include <core/ga/crossover_fabric.h>

/**
 * @struct MCPTable
 * Concentra os dados de armazenamento da tabela do porblema do clique máximo */
struct MCPTable : public TableController {
public:
  int solution_size;
  int total_cost;
  std::string solution;

  explicit MCPTable()
  : TableController("maxclique_executions"), solution_size(0), total_cost(0),
    solution(std::string()) {}

  MCPTable(CLI *cli);

  ~MCPTable();

  void create(sqlite::connection *con);

  void insert(sqlite::connection *con);
};

#endif