#include <iostream>
#include <string>
#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoTimeContinue.h>
#include <paradiseo/eo/eoRankingSelect.h>
// #include <paradiseo/eo/eoDetTournamentSelect.h>
#include <core/cli/parse.h>
#include <core/ga/encoding.h>
#include <core/ga/random.h>
#include <core/ga/crossover_fabric.h>
#include <core/ga/genetic_algorithm.h>
#include <core/utils/split.h>
#include <core/time_parse.hpp>
#include <core/db/create.hpp>
#include <core/db/entry.hpp>

#include "mknap_problem.h"

using Str = std::string;
#define PRINT(txt) std::cout << txt << std::flush
#define PRINTLN(txt) std::cout << txt << std::endl
#define SEPLINE(n) \
  for (int i=0; i < n; i++) { \
    std::cout << '-'; \
  } \
  std::cout << std::endl
#define UEC(number) "\e[38;5;"+ std::to_string(number) +"m"

void searchCallback (int g, eoPop<Chrom> &p) {
  std::cout << "G" << g << " -- Melhor fitness: "
      << p.best_element().fitness() << std::endl;
}


int exec(int argc, char **argv) {
  auto args = parse(argc, argv);
  auto filename = *(split(Str(args->infile), '/').end()-1);
  std::cout << "Problema da Mochila Multi-dimensional: " << filename << std::endl;
  SEPLINE(60);
  std::cout << *args;
  SEPLINE(60);

  MKnapsackProblem mkp(args->infile);
  mkp.display_info(std::cout);
  SEPLINE(60);

  PRINT("Inicializando população");
  auto pop = mkp.init_pop(args->pop_size);
  PRINTLN("\rPopulação inicializada!");

  

  return 0;
}


int main(int argc, char **argv) {
  try {
    return exec(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "Exception catched: " << e.what() << std::endl;
    return 127;
  }
  return 0;
}
