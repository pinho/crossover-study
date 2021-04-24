#include <iostream>
#include <core/cli/parse.h>
#include <core/db/database.hpp>

#include "maximum_weighted_clique_problem.h"
#include "mcp_database.hpp"
#include "../Runner.h"

int main(int argc, char **argv) {
  CLI *args = parse(argc, argv);

  Runner<MWCProblem, MCPModel> r(args->infile);

  // Executa todo o processo de preparação, evolução,
  // e organização dos dados de saída
  r(args);

  if (args->using_db) {
    try {
      MCPModel model = r.get_model();
      model.solution_size = r.get_solution_size();
      model.solution = r.get_formatted_solution();
      model.total_cost = r.get_solution_total_cost();
    
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

