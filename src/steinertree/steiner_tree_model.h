#ifndef STEINER_TREE_MODEL_H_
#define STEINER_TREE_MODEL_H_

#include <core/db/base_model.hpp>
#include <core/ga/crossover_fabric.h>
#include <core/utils/trim_filename.h>
#include <core/cli/options.h>

class SteinerTreeModel : public db::BaseModel {
public:
  int num_steiner_nodes;
  std::string steiner_nodes;
  float total_costs;

  SteinerTreeModel();
  SteinerTreeModel(CLI*);
  ~SteinerTreeModel() = default;

  /**
   * @brief define os valores relacionados à solução obtida (numéro de vértices
   * de Steiner; Os vértices de Steiner; custo total da árvore) */
  void set_solution_data(std::vector<int>& solutionNodes);

  void create(sqlite::connection *con);
  void insert(sqlite::connection *con);
};

#endif
