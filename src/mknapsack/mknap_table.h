#ifndef MKNAP_TABLE_H_
#define MKNAP_TABLE_H_

#include <core/db/table_controller.hpp>
#include <core/ga/crossover_fabric.h>
#include <core/cli/options.h>

class MKnapTable : public TableController {
public:
  int num_items;
  std::string solution;
  float total_costs;

  MKnapTable();

  MKnapTable(CLI *cli);

  void create(sqlite::connection *con);

  void insert(sqlite::connection *con);
};

#endif