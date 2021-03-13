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

#include "maximum_weighted_clique_problem.h"
#include "mcp_database.hpp"
using namespace std::chrono;

#define sepline(n) \
  for (int i=0; i < n; i++) std::cout << '-'; \
  std::cout << std::endl

// Unix Escape Color
#define UNIX_COLOR(number) "\e[38;5;"+ std::to_string(number) +"m"

/**
 * Função executada dentro do algortimo genético a cada geração após os
 * a aplicação dos operadores genéticos */
void evolutionCallback (int g, eoPop<Chrom> &p) {
  std::cout << "G" << g << "\t";
  auto x = p.it_best_element();
  std::cout << "Clique de " << std::accumulate(x->begin(), x->end(), 0);
  std::cout << " vértices\n\tPeso do clique: ";
  std::cout << x->fitness() << '\n';
  sepline(30);
}


int main(int argc, char **argv)
{
  CLI *args = parse(argc, argv);
  auto filename = *(split(std::string(args->infile), '/').end()-1);

  // Instanciação do objeto do problema do clique máximo com pesos nos vértices.
  // A instância da classe MWCProblem possui a matriz de adjacências do grafo
  // e os pesos correspondentes aos vértices, assim como os métodos que lidarão
  // diretamente com os cromossomos, como o reparo de solução e a função
  // objetivo.
  MWCProblem mc(args->infile);
  std::cout << "Matrix inicializada: arquivo " << filename << std::endl;
  // sepline(60);
  // std::cout << *args;
  // sepline(60);
 
  // Geração da população inicial
  auto pop = mc.init_pop(args->pop_size, 0.25);
  std::cout << "População inicializada" << std::endl;

  // Avaliando população inicial
  // sepline(60);
  // std::cout << "Avaliando população inicial";
  mc.eval(pop);
  // std::cout << "\rPopulação inicial avaliada " << std::endl;
  // std::cout << pop.best_element() << std::endl;

  // Definição dos parâmetros do AG
  eoGenContinue<Chrom> term(args->epochs);
  eoBitMutation<Chrom> mutation(args->mutation_rate);
  eoDetTournamentSelect<Chrom> select(args->tour_size);
  auto *crossover = CrossoverFabric::create(args->crossover_id);

  // Define a instância da classe de Algoritmo genético
  GeneticAlgorithm ga(
      mc, select, *crossover, args->crossover_rate, mutation, 1.0f, term);
  // sepline(60);

  // std::cout << "Iniciando evolução" << std::endl;
  // Vector de convergências
  std::vector<Chrom> conv;

  // Execução da evolução
  auto start_point = system_clock::now();
  ga(pop, conv, evolutionCallback);
  auto dur_ns = system_clock::now() - start_point; // Duração em nanosegundos

  // Solução final
  Chrom melhor = pop.best_element();
  unsigned int finalcost = (uint) melhor.fitness();
  std::cout << "Peso do Clique: " << finalcost << std::endl;

  // Iterações pelo cromossomo pegando os índices dos genes '1' para definir
  // os vértices que fazem parte da solução final encontrada
  std::vector<int> solution;
  std::cout << "Vértices:\n";
  for (size_t i = 0; i < melhor.size(); i++) {
    if (melhor[i]) {
      solution.push_back(i+1);
      std::cout << i+1 << " ";
    }
  }
  std::cout << std::endl;

  if (args->using_db) {
    // Configura a tabela
    MCPModel execution(args);
    execution.instance_file = filename;
    execution.duration_in_ms = duration_cast<milliseconds>(dur_ns).count();
    execution.set_convergence(conv);
    execution.solution_size = std::accumulate(melhor.begin(), melhor.end(), 0);
    execution.solution = MCPModel::sequence_to_string<int>(solution);
    execution.total_cost = (int) finalcost;
    // Conecta com o banco
    db::Database db(args->databasefile);
    db.set_model(&execution);
    db.exec_insertion();
  }
  return 0;
}

