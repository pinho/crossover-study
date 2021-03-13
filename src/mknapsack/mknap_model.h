#ifndef MKNAP_TABLE_H_
#define MKNAP_TABLE_H_

#include <core/db/base_model.hpp>
#include <core/ga/crossover_fabric.h>
#include <core/cli/options.h>

class MknapModel : public db::BaseModel {
public:
  int num_items;
  std::string solution;
  float total_costs;

  MknapModel();

  MknapModel(CLI *cli);

  void create(sqlite::connection *con);

  void insert(sqlite::connection *con);
};

#endif
