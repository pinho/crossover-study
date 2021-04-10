#include <iostream>
#include <core/cli/parse.h>
#include <core/db/database.hpp>

#define DEBUG 1

#include "set_covering_problem.h"
#include "scp_model.h"
#include  "../Runner.h"

int main(int argc, char **argv) {
  using SCP = SetCoveringProblem;
  CLI *args = parse(argc, argv);

  Runner<SCP, SCPModel> r(args->infile);
  r(args);

  if (args->using_db) {
    try {
      SCPModel model = r.get_model();
      model.num_columns = r.get_solution_size();
      model.columns = r.get_formatted_solution();
      model.total_costs = r.get_solution_total_cost();

      db::Database db(args->databasefile);
      db.set_model(&model);
      db.exec_insertion();
    }
    catch(std::exception &e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
