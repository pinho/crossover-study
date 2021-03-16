#include <cstdlib>
#include <iostream>
#include <core/cli/parse.h>
#include <core/db/database.hpp>

#include "steiner_tree.h"
#include "steiner_tree_model.h"
#include  "../Runner.h"

int main(int argc, char **argv) {
  using STP = SteinerTreeProblem;
  CLI *args = parse(argc, argv);

  Runner<STP,SteinerTreeModel> r(args->infile);
  r(args);

  if (args->using_db) {
    try {
      SteinerTreeModel model = r.get_model();
      model.num_steiner_nodes = r.get_solution_size();
      model.steiner_nodes = r.get_formatted_solution();
      model.total_costs = r.get_solution_total_cost();

      db::Database db(args->databasefile);
      db.set_model(&model);
      db.exec_insertion();
    }
    catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
