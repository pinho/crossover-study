#ifndef STEINER_TREE_TABLE_H_
#define STEINER_TREE_TABLE_H_

#include <core/db/table_controller.hpp>
#include <core/ga/crossover_fabric.h>
#include <core/utils/trim_filename.h>
#include <core/cli/options.h>

class SteinerTreeTable : public TableController {
public:
  int num_steiner_nodes;
  std::string steiner_nodes;
  float total_costs;

  SteinerTreeTable();
  SteinerTreeTable(CLI*);
  ~SteinerTreeTable() = default;

  /**
   * @brief define os valores relacionados à solução obtida (numéro de vértices
   * de Steiner; Os vértices de Steiner; custo total da árvore) */
  void set_solution_data(std::vector<int>& solutionNodes);

  void create(sqlite::connection *con);
  void insert(sqlite::connection *con);
};

#endif