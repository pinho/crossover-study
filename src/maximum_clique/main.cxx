#include <iostream>
#include <string>
#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoTimeContinue.h>
#include <paradiseo/eo/eoRankingSelect.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>

#include <core/cli/parse.h>
#include <core/ga/encoding.h>
#include <core/ga/random.h>
#include <core/ga/crossover_fabric.h>
#include <core/ga/genetic_algorithm.h>
#include <core/utils/split.h>
#include <core/utils/parse_duration.h>
#include <core/db/database.hpp>

#include "maximum_clique_problem.h"
#include "mcp_database.hpp"

#define sepline(n) \
  for (int i=0; i < n; i++) std::cout << '-'; \
  std::cout << std::endl

// Unix Escape Color
#define UNIX_COLOR(number) "\e[38;5;"+ std::to_string(number) +"m"

using Str = std::string;


/**
 * Função executada dentro do algortimo genético a cada geração após os
 * a aplicação dos operadores genéticos */
void evolutionCallback (int g, eoPop<Chrom> &p) {
  std::cout << "G" << g << "\t";
  std::cout << "Tamanho do clique: " << p.best_element().fitness();
  std::cout << std::endl;
}


int exec(int argc, char **argv) {
  using namespace std::chrono;
  std::cout << "\e[1;3m\e[38;5;47mProblema do Clique Máximo\e[0m" << std::endl;

  CLI *args = parse(argc, argv);
  auto filename = *(
    split(Str(args->infile), '/').end()-1
  );

  // leitura do arquivo de definição do grafo e instanciação do problema
  MCProblem mc(args->infile);
  std::cout << "Matrix inicializada: arquivo " << filename << std::endl;

  sepline(60);
  std::cout << *args;
  sepline(60);

  // Geração da população inicial
  auto pop = mc.init_pop(args->pop_size, 0.25);
  std::cout << "População inicializada" << std::endl;

  // Avaliando população inicial
  sepline(60);
  std::cout << "Avaliando população inicial";
  mc.eval(pop);
  std::cout << "\rPopulação inicial avaliada " << std::endl;

  // Definição dos parâmetros do AG
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation(args->mutation_rate);
  eoDetTournamentSelect<Chrom> select(args->tour_size);
  auto *crossover = CrossoverFabric::create(args->crossover_id);

  // define a instância da classe de Algoritmo genético
  GeneticAlgorithm ga(
    mc, select, *crossover, args->crossover_rate, mutation, 1.0f, term);
  sepline(60);

  std::cout << "Iniciando evolução" << std::endl;

  // Vector de convergências
  std::vector<Chrom> conv;

  // Execução da evolução
  auto start_point = system_clock::now();
  ga(pop, conv, evolutionCallback);
  auto dur_ns = system_clock::now() - start_point; // Duração em nanosegundos

  // Solução final
  sepline(60);
  Chrom melhor = pop.best_element();
  std::vector<int> solution;

  std::cout << "Melhor solução:\n";
  std::cout << "Clique de " << (uint) melhor.fitness() << " vértices\n";
  std::cout << "Vértices:\n";

  // Iterações pelo cromossomo pegando os índices dos genes '1' para definir
  // os vértices que fazem parte da solução final encontrada
  for (size_t i = 0; i < melhor.size(); i++) {
    if (melhor[i]) {
      solution.push_back(i+1);
      std::cout << i+1 << " ";
    }
  }
  std::cout << std::endl;

  if (args->using_db) {
    // Configura a tabela
    MCPTable tb(args);
    tb.instance_file = filename;
    tb.duration_in_ms = duration_cast<milliseconds>(dur_ns).count();
    tb.set_convergence(conv);
    tb.solution_size = (int) melhor.fitness();
    tb.solution = MCPTable::sequence_to_string<int>(solution);
    // Conecta com o banco
    Database db(args->databasefile);
    db.set_controller(&tb);
    db.insert_data();
  }

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
