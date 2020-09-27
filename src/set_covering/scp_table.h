#ifndef SCP_TABLE_H_
#define SCP_TABLE_H_

#include <core/db/table_controller.hpp>
#include <core/ga/crossover_fabric.h>
#include <core/utils/trim_filename.h>
#include <core/cli/options.h>

class SCPTable : public TableController {
public:
  int num_columns;
  std::string columns;
  float total_costs;

  SCPTable();
  SCPTable(CLI *cli);
  ~SCPTable() = default;

  void create(sqlite::connection *con);
  void insert(sqlite::connection *con);
};

#endif