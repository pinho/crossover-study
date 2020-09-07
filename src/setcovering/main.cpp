#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;

#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoTimeContinue.h>
#include <paradiseo/eo/eoRankingSelect.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
#include <sqlite/database_exception.hpp>
#include <core/cli/parse.h>
#include <core/ga/genetic_algorithm.h>
#include <core/ga/crossover_fabric.h>
// #include <core/ga/entropy.h>
#include <core/db/create.hpp>
#include <core/db/entry.hpp>
#include <core/time_parse.hpp>

#include "scp_matrix.h"
#include "set_covering_problem.h"

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
 * Corta o caminho do arquivo reduzindo-o a somente o
 * nome do arquivo */
const char* trim_filename(const char *filename) {
  std::string str_filename(filename);
  return (split(str_filename, '/').end()-1)->c_str();
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
  // std::cout << "\tEntropia da pop.: " << Entropy::overall(pop) ;
  std::cout << std::endl;
}

/**
 * Função de execução d programa principal inteiro
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
  auto pop = prob.init_pop( args->pop_size );
  std::cout << "[" << green("done") << "]" << std::endl;

  std::cout << "Avaliando população inicial " << std::flush;
  prob.eval(pop);
  // std::cout << pop << std::endl;

  // Definição do Algoritmo genético e operadores
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation( args->mutation_rate );
  eoDetTournamentSelect<Chrom> select(args->tour_size);
  auto *crossover = CrossoverFabric::create(args->crossover_id);
  GeneticAlgorithm ga(
    prob, select, *crossover, args->crossover_rate, mutation, 1.0f, term);

  // Início da execução do AG
  break_lines(std::cout);
  std::cout << green("Iniciando evolução") << std::endl;
  std::vector<Chrom> convergence;

  auto start_point = system_clock::now();
  ga(pop, convergence, ga_callback);
  auto end_point   = system_clock::now();

  break_lines(std::cout);
  Chrom best = pop.best_element();
  auto best_cost = 1 / best.fitnessReference();
  std::cout << "Custo da melhor solução: " << best_cost << std::endl;
  std::cout << std::accumulate(best.cbegin(), best.cend(), 0)
            << " colunas escolhidas: ";
  
  std::vector<unsigned int> cols;
  for (int i=0; i < best.size(); i++) {
    if (best[i]) {
      std::cout << i+1 << " ";
      cols.push_back(i+1);
    }
  }
  std::cout << std::endl;

  // Escrita dos dados no arquivo de banco de dados
  if (args->using_db) {
    auto duration = duration_cast<milliseconds>(end_point - start_point);

    try {
      auto conn = db_create(args->databasefile, db_structure::sc);
      db_setcovering_entry(*conn, args, convergence, cols, best_cost,
              instance_filename, duration);
      break_lines(std::cout);
      std::cout << "Dados gravados em " << args->databasefile << std::endl;
    }
    catch (sqlite::database_exception) {
      std::cerr << "Não pode escrever no arquivo " << args->databasefile << std::endl;
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
    std::cerr << "Exception at main(): \"" << e.what() << "\"" << std::endl;
    return 1;
  }
  return 0;
}