#include <iostream>
#include <core/cli/parse.h>
#include <core/db/database.hpp>

#include "mknap_problem.h"
#include "mknap_model.h"
#include  "../Runner.h"

int main(int argc, char **argv) {
  using MKP = MKnapsackProblem;
  CLI *args = parse(argc, argv);

  Runner<MKP, MknapModel> r(args->infile);
  r(args);

  if (args->using_db) {
    try {
      MknapModel model = r.get_model();
      model.num_items = r.get_solution_size();
      model.solution = r.get_formatted_solution();
      model.total_costs = r.get_solution_total_cost();

      db::Database db(args->databasefile);
      db.set_model(&model);
      db.exec_insertion();
    } catch(std::exception &e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

