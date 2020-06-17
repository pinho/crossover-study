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

#include "maximum_clique_problem.h"

#define print(txt) std::cout << txt << std::flush
#define println(txt) std::cout << txt << std::endl
#define println_bgred(txt) std::cout << "\e[48;5;196m " << txt << " \e[0m" << std::endl
#define sepline(n) \
  for (int i=0; i < n; i++) { \
    std::cout << '-'; \
  } \
  std::cout << std::endl

using Str = std::string;

matrix *M;


int exec(int argc, char **argv) {
  auto args = parse(argc, argv);

  auto filename = *(
    split(Str(args->infile), '/')
      .end()-1
  );

  // leitura do arquivo de definição do grafo e instanciação do problema
  MCProblem mc(args->infile);
  println("Matrix inicializada: arquivo " << filename);

  sepline(60);
  std::cout << *args;
  sepline(60);

  // Geração da população inicial
  auto pop = mc.init_pop(args->pop_size, 0.2);
  println("População inicializada");

  // Avaliando população inicial
  sepline(60);
  print("Avaliando população inicial");
  mc.eval(pop);
  println("\rPopulação inicial avaliada ");

  // pop.sort();
  // println("Fitnesses da população inicial:");
  // for (auto& chrom : pop) {
  //   std::cout << chrom.fitness() << " ";
  // }
  // std::cout << std::endl;
  sepline(60);

  // Definição dos parâmetros do AG
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoRankingSelect<Chrom> select;

  auto *crossover = CrossoverFabric::create(args->crossover_id);
  auto crossover_name = CrossoverFabric::name(args->crossover_id);

  GeneticAlgorithm ga(
    mc, select, *crossover, args->crossover_rate, mutation, 1.0f, term);

  sepline(60);
  println_bgred("Iniciando evolução");

  std::vector<Chrom> conv;
  ga(pop, conv, [](int g, eoPop<Chrom> &p) {
  #ifdef __unix__
    std::cout << "\e[48;5;88m " << std::flush;
  #endif
  std::cout << "G" << g << " -- Melhor fitness: " << p.best_element().fitness();
  #ifdef __unix__
    std::cout << " \e[0m" << std::endl;
  #endif
  });

  // Solução final
  Chrom melhor = pop.best_element();
  println("\nMelhor solução:");

  println("Clique de " << melhor.fitness() << " vértices");
  print("Vértices: ");
  for (size_t i = 0; i < melhor.size(); i++) {
    if (melhor[i])
      print(i << " ");
  }
  std::cout << std::endl;

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