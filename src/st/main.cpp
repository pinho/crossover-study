#include <cstdlib>
#include <iostream>
#include <chrono>
using std::chrono::system_clock;

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoTimeContinue.h>
#include <paradiseo/eo/eoRankingSelect.h>
#include <core/cli/parse.h>
#include <core/ga/crossover_fabric.h>
#include <core/ga/genetic_algorithm.h>
#include "steiner_tree.h"
#include "graph.h"

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
  std::cout << "Parâmetros:\n";
  std::cout << *args;

  SteinerTreeProblem stein(args->infile);
  sep_line(60);
  stein.display_info(std::cout);

  sep_line(60);
  std::cout << "Inicializando população ..." << std::flush;
  auto population = stein.init_pop( args->pop_size );
  std::cout << population << std::endl;

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
  auto melhor = population.best_element();
  float melhor_custo = (float) (1/melhor.fitness());

  std::cout << "Melhor custo obtido: " << melhor_custo << std::endl;

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