#ifndef SCP_TABLE_H_
#define SCP_TABLE_H_

#include <core/db/base_model.hpp>
#include <core/ga/crossover_fabric.h>
#include <core/utils/trim_filename.h>
#include <core/cli/options.h>

class SCPModel : public db::BaseModel {
public:
  int num_columns;
  std::string columns;
  float total_costs;

  SCPModel();
  SCPModel(CLI *cli);
  ~SCPModel() = default;

  void create(sqlite::connection *con);
  void insert(sqlite::connection *con);
};

#endif
