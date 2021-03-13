#include <iostream>
#include <iomanip>
// #include <string>
#include <cstdio>
#include <chrono>
using std::chrono::system_clock;

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoSelectOne.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
#include <core/cli/parse.h>
#include <core/ga/crossover_fabric.h>
#include <core/ga/genetic_algorithm.h>
#include <core/utils/parse_duration.h>
#include <core/utils/trim_filename.h>
#include <core/db/database.hpp>

#include "mknap_problem.h"
#include "mknap_model.h"

#define SEPLINE(n) \
  for (int i=0; i < n; i++) { \
    std::cout << '-'; \
  } \
  std::cout << std::endl
#define UEC(number) "\e[38;5;"+ std::to_string(number) +"m"

void evolutionCallback (int g, eoPop<Chrom> &p) {
  std::cout << "G" << g << " Valor da melhor combinação de items: ";
  std::cout << p.best_element().fitness() << std::endl;
}


int exec(int argc, char **argv) {
  CLI *args = parse(argc, argv);
  auto filename = *(split(std::string(args->infile), '/').end()-1);

  std::cout <<"Problema da Mochila Multi-dimensional: "<< filename <<std::endl;
  SEPLINE(60);
  std::cout << *args;
  SEPLINE(60);

  MKnapsackProblem mkp(args->infile);
  mkp.display_info(std::cout);
  SEPLINE(60);

  std::cout << "Inicializando população...";
  auto pop = mkp.init_pop(args->pop_size);
  std::cout << "\rPopulação inicializada!  " << std::endl;

  std::cout << "Avaliando população inicial" << std::endl;
  mkp.eval(pop);

  // Definição dos parâmetros do AG
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoDetTournamentSelect<Chrom> select(args->tour_size);
  auto *crossover = CrossoverFabric::create(args->crossover_id);

  // define a instância da classe de Algoritmo genético
  GeneticAlgorithm ga(
    mkp, select, *crossover, args->crossover_rate, mutation, 1.0f, term);
  SEPLINE(60);
  std::cout << "Iniciando evolução" << std::endl;

  // Execução da evolução
  auto start_point = system_clock::now();
  ga(pop);
  nanoseconds duration = system_clock::now() - start_point;

  Chrom melhor = pop.best_element();
  // std::vector<float> &objectValues = mkp.profits();
  std::vector<uint> indices;

  SEPLINE(60);
  auto cost = melhor.fitness();
  std::cout << "Custo total: " << cost << std::endl;

  // Mostra informações sobre o resulto final obtido em relação a solução ótima
  // ou mlehor solução conhecida se ela estiver definida no arquivo de instância
  if (mkp.optimal() > 0.0f) {
    std::cout << (melhor.fitness() / mkp.optimal())*100 << "\% de aproximação.";
    std::cout << "\nSolução ótima: "<< mkp.optimal() << std::endl;
  }

  SEPLINE(60);

  // Quando a opção --db é usada para definir um arquivo de banco de dados
  if (args->using_db) {
    using namespace std::chrono;

    MknapModel tb(args);
    tb.instance_file = filename;
    tb.duration_in_ms = (double) duration_cast<milliseconds>(duration).count();
    auto conv = ga.get_convergence();
    tb.set_convergence(conv);
    tb.solution = MknapModel::sequence_to_string(indices);
    tb.num_items = (int) indices.size();
    tb.total_costs = (float) cost;
    
    db::Database db(args->databasefile);
    db.set_model(&tb);
    db.exec_insertion();

    std::cout << "Dados salvos em " << args->databasefile << std::endl;
  }

  return 0;
}


int main(int argc, char **argv) {
  try {
    return exec(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "Exception on main: " << e.what() << std::endl;
    return 127;
  }
  return 0;
}
