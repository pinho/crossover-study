#include <iostream>
#include <iomanip>
#include <cstdio>
#include <chrono>
using namespace std::chrono;

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoRankingSelect.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
#include <sqlite/database_exception.hpp>
#include <core/cli/parse.h>
#include <core/ga/crossover_fabric.h>
#include <core/db/create.hpp>
#include <core/db/entry.hpp>
#include <core/db/database.hpp>
#include <core/utils/parse_duration.h>
#include <core/utils/trim_filename.h>
#include <core/utils/logger.h>

#include "set_covering_problem.h"
#include "genetic_algorithm_scp.h"
#include "decoder.h"

#define green(msg) "\e[1;32m" + std::string(msg) + "\e[0m"

/**
 * Printa vários "-" para separar a linha anterior da próxima no log.
 * O número padrão de "-"s é 60 */
inline void break_lines(std::ostream &os, unsigned short __n = 60) {
  unsigned short n = 0;
  while (n++ < __n)
    os << '-';
  os << std::endl;
}

/**
 * Funçção de callback entre as geração do algoritmo genético */
void ga_callback(int generation, eoPop<Chrom>& pop) {
  std::cout << "[" << generation << "a geração] ";
  std::cout << "Melhor custo: ";
#ifdef __unix__
  std::cout << "\e[38;5;27m" << (int) (1 / pop.it_best_element()->fitness()) << "\e[0m";
#else
  std::cout << (int) (1 / pop.it_best_element()->fitness());
#endif
  std::cout << std::endl;
}

/**
 * Função de execução do programa principal inteiro
 */
int exec(CLI *args) {
  auto instance_filename = std::string( trim_filename(args->infile) );
  std::cout << "Cobertura de conjuntos: " << instance_filename << std::endl;
  break_lines(std::cout);

  SetCoveringProblem prob(args->infile);
  prob.display_info(std::cout);
  break_lines(std::cout);

  std::cout << *args;
  break_lines(std::cout);

  std::cout << "Inicializando população " << std::flush;
  auto pop = prob.init_pop( args->pop_size, 0.3 );
  std::cout << "[" << green("done") << "]" << std::endl;

  std::cout << "Avaliando população inicial " << std::flush;
  prob.eval(pop);
  // std::cout << pop << std::endl;

  // Definição do Algoritmo genético e operadores
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoDetTournamentSelect<Chrom> select(args->tour_size);
  auto *crossover = CrossoverFabric::create(args->crossover_id);

  scp::GeneticAlgorithmSCP ga(
    prob, select,
    *crossover, args->crossover_rate, 
    mutation, 0.75, 
    term);

  // Preparando para iniciar a execução
  break_lines(std::cout);
  std::cout << green("Iniciando evolução") << std::endl;
  std::vector<Chrom> convergence;

  // Início da execução do algoritmo
  auto start_point = system_clock::now();
  ga(pop, convergence, ga_callback);
  auto end_point   = system_clock::now();
  nanoseconds dur_ns = end_point - start_point;

  break_lines(std::cout);
  std::cout << std::fixed << "Tempo de evolução: "
            << parse_duration(dur_ns) << std::endl;

  break_lines(std::cout);
  Chrom best = pop.best_element();
  auto best_cost = 1 / best.fitness();

  std::cout << std::accumulate(best.cbegin(), best.cend(), 0)
            << " colunas escolhidas. Custo:  "
            << (int) best_cost
            << std::endl;
  
  // Escrita dos dados no arquivo de banco de dados
  if (args->using_db) {
    std::vector<unsigned int> cols = Decoder::solution(best);
    milliseconds duration = duration_cast<milliseconds>(end_point - start_point);

    try {
      auto conn = db_create(args->databasefile, db_structure::sc);
      db_setcovering_entry(*conn, args, convergence, cols, best_cost,
          instance_filename, duration);
      break_lines(std::cout);
      std::cout << "Dados gravados em " << args->databasefile << std::endl;
    }
    catch (sqlite::database_exception& e) {
      std::cerr << "Não pode escrever no arquivo " << args->databasefile << std::endl;
      return 2;
    }
  }

  return 0;
}


/**
 * Função principal:
 * Encapsula a execução do programa todo com um bloco try/catch para
 * lidar com possíveis exceções não tratadas
 */
int main(int argc, char **argv) {
  try {
    CLI* arguments = parse(argc, argv);
    return exec(arguments);
  }
  catch (std::exception& e) {
    std::cerr << __func__ << " -> " << e.what() << std::endl;
    return 1;
  }
  return 0;
}