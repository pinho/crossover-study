#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoSelectOne.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
#include <core/cli/parse.h>
#include <core/ga/genetic_algorithm.h>
#include <core/utils/parse_duration.h>
#include <core/utils/trim_filename.h>
#include <core/db/database.hpp>

#include "steiner_tree.h"
#include "steiner_tree_model.h"
#include "graph.h"

#define UNIX_COLOR(number) "\e[38;5;"+ std::to_string(number) +"m"
#define green(output) UNIX_COLOR(113) + std::string(output) + UNIX_COLOR(0)

/**
 * Printa uma sequência de traços para separar linhas de log */
void sep_line(unsigned int n) {
  size_t i = 0;
  do { std::cout << "-"; } while (i++ < n);
  std::cout << std::endl;
}

/**
 * Função pra executar a cada geração do Algoritmo Genético
 */
void ga_callback(int gen, eoPop<Chrom> &pop) {
  float fitness = pop.best_element().fitness();
  std::cout << gen << "a geração: " << " Custo = " << 1/fitness << std::endl;
}


int exec(CLI *args) {
  sep_line(60);
  auto filename = std::string(trim_filename(args->infile));
  std::cout << "Parâmetros\n";
  std::cout << *args;

  SteinerTreeProblem stein(args->infile);
  sep_line(60);
  stein.display_info(std::cout);

  sep_line(60);
  std::cout << "Inicializando população ..." << std::endl;
  auto population = stein.init_pop( args->pop_size );

  sep_line(60);
  std::cout << "Avaliando população inicial ..." << std::endl;
  stein.eval( population );

  // Definição do Algoritmo genético e operadores
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoDetTournamentSelect<Chrom> select(args->tour_size);
  auto *crossover = CrossoverFabric::create(args->crossover_id);
  GeneticAlgorithm ga(stein, select,
      *crossover, args->crossover_rate, mutation, 1.0f, term);

  std::cout << "Iniciando evolução" << std::endl;
  sep_line(60);

  auto start_point = system_clock::now();
  ga(population);
  auto duration = system_clock::now() - start_point;

  sep_line(60);

  // Decodificação da solução final e informações associadas
  Chrom best_individual = population.best_element();
  float best_cost = float(1/best_individual.fitness());
  std::cout << "\e[0mMelhor custo obtido: " << best_cost << std::endl;

  auto *steiner_nodes = stein.steiner_nodes();
  std::vector<int> solution_vec;

  std::cout << "Vértices de Steiner: ";
  for (size_t i=0; i < stein.get_chromsize(); i++) {
    std::cout << " ";
    if (best_individual[i]) {
      std::cout << "\e[38;5;40m";
      solution_vec.push_back(steiner_nodes->at(i));
    }
    std::cout << steiner_nodes->at(i) << "\e[0m";
  }
  std::cout << std::endl;

  // Integração com banco de dados sqlite
  if (args->using_db) {
    auto duration_in_ms = duration_cast<milliseconds>(duration);

    try {
      SteinerTreeModel execution(args);
      execution.set_convergence(ga.get_convergence());
      execution.instance_file = filename;
      execution.duration_in_ms = duration_in_ms.count();
      execution.set_solution_data(solution_vec);
      execution.total_costs = best_cost;

      db::Database db(args->databasefile);
      db.set_model(&execution);
      db.exec_insertion();

      std::cout << "Dados salvos em " << args->databasefile << std::endl;
    }
    catch (sqlite::database_exception& e) {
      std::cerr << "Erro de banco de dados: " << e.what() << std::endl;
      exit(1);
    }
  }

  return 0;
}

// MAIN FUNCTION

int main(int argc, char **argv) {
  try {
    CLI* args = parse(argc, argv);
    return exec(args);
  } catch (std::exception &e) {
    std::cerr << "Main was catched: " << e.what() << std::endl;
    return 127;
  }
  return 0;
}
