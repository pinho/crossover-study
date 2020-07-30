#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
using std::chrono::system_clock;

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

  auto weightsMatrix = mkp.get_weights();
  for (int i=0; i < weightsMatrix->size(); i++) {
    for (int k=0; k < weightsMatrix->at(0).size(); k++) {
      std::cout << std::setw(4) << weightsMatrix->at(i).at(k);
    }
    std::cout << std::endl;
  }

  PRINT("Inicializando população");
  auto pop = mkp.init_pop(args->pop_size);
  PRINTLN("\rPopulação inicializada!");

  PRINT("Avaliando população");
  mkp.eval(pop);

  // Definição dos parâmetros do AG
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoRankingSelect<Chrom> select;
  auto *crossover = CrossoverFabric::create(args->crossover_id);

  // define a instância da classe de Algoritmo genético
  GeneticAlgorithm ga(
    mkp, select, *crossover, args->crossover_rate, mutation, 1.0f, term);
  SEPLINE(60);
  std::cout << UEC(47) << "Iniciando evolução" << UEC(255) << std::endl;

  // Vector de convergências
  std::vector<Chrom> conv;

  // Execução da evolução
  auto start_point = std::chrono::system_clock::now();
  ga(pop, conv, searchCallback);
  auto dur_ns = system_clock::now() - start_point; // Duração em nanosegundos

  // Converter duração para segundos
  std::cout << std::fixed << "Tempo de evolução: " << UEC(47)
            << parse_duration(dur_ns) << UEC(255) << std::endl;

  // TODO: Impressão da solução final
  

  // TODO: Armazenamento no banco de dados

  return 0;
}


int main(int argc, char **argv) {
  try {
    return exec(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "\nmain: " << e.what() << std::endl;
    return 127;
  }
  return 0;
}
