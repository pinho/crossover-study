#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoTimeContinue.h>
#include <paradiseo/eo/eoRankingSelect.h>
#include <sqlite/database_exception.hpp>
#include <core/cli/parse.h>
#include <core/ga/crossover_fabric.h>
#include <core/ga/genetic_algorithm.h>
#include <core/db/create.hpp>
#include <core/db/entry.hpp>
#include <core/utils/parse_duration.h>
#include "steiner_tree.h"
#include "graph.h"

#define UEC(number) "\e[38;5;"+ std::to_string(number) +"m"

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
  std::cout << gen << "a geração: " << " Fitness = "
    << pop.best_element().fitness() << std::endl;
}


int exec(CLI *args) {
  sep_line(60);
  auto filename = *(split(std::string(args->infile), '/').end()-1);
  std::cout << "Parâmetros\n";
  std::cout << *args;

  SteinerTreeProblem stein(args->infile);
  sep_line(60);
  stein.display_info(std::cout);

  sep_line(60);
  std::cout << "Inicializando população ..." << std::flush;
  auto population = stein.init_pop( args->pop_size );
  // std::cout << population << std::endl;

  sep_line(60);
  std::cout << "Avaliando população inicial ..." << std::flush;
  stein.eval( population );

  // Definição do Algoritmo genético e operadores
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoRankingSelect<Chrom> select;
  auto *crossover = CrossoverFabric::create(args->crossover_id);
  GeneticAlgorithm ga(
    stein, select, *crossover, args->crossover_rate, mutation, 1.0f, term);

  std::cout << "Iniciando evolução" << std::endl;
  sep_line(60);
  std::vector<Chrom> conv;
  auto start_point = system_clock::now();
  ga(population, conv, ga_callback); // algoritmo é executado aqui
  auto evolving_duration = system_clock::now() - start_point;

  sep_line(60);
  // Converter duração para segundos
  std::cout << std::fixed << "Tempo de evolução: " << UEC(47)
            << parse_duration(evolving_duration) << UEC(255) << std::endl;

  auto melhor = population.best_element();
  float melhor_custo = (float) (1/melhor.fitness());
  std::cout << "Melhor custo obtido: " << melhor_custo << std::endl;

  auto *steiner_nodes = stein.steiner_nodes();
  std::vector<uint> solution_vec;

  std::cout << "Vértices de Steiner: ";
  for (size_t i=0; i < stein.get_chromsize(); i++) {
    std::cout << " ";
    if (melhor[i]) {
      std::cout << "\e[38;5;40m";
      solution_vec.push_back(steiner_nodes->at(i));
    }
    std::cout << steiner_nodes->at(i) << "\e[0m";
  }
  std::cout << std::endl;

  // Integração com banco de dados sqlite
  if (args->using_db) {
    sep_line(60);
    auto duration_in_ms = duration_cast<milliseconds>(evolving_duration);

    try {
      auto conn = db_create(args->databasefile, db_structure::st);
      db_steinertree_entry(*conn, args, conv, solution_vec, melhor_custo,
          filename, duration_in_ms);

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
