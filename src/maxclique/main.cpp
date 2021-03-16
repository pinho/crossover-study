#include <iostream>
#include <core/cli/parse.h>
#include <core/db/database.hpp>

#include "maximum_weighted_clique_problem.h"
#include "mcp_database.hpp"
#include "../Runner.h"

int main(int argc, char **argv) {
  CLI *args = parse(argc, argv);

  Runner<MWCProblem, MCPModel> r(args->infile);
  r(args);

  if (args->using_db) {
    try {
      MCPModel model = r.get_model();
      model.solution_size = r.get_solution_size();
      model.solution = r.get_formatted_solution();
      model.total_cost = r.get_solution_total_cost();
    
      db::Database db(args->databasefile);
      db.set_model(&model);
      db.exec_insertion();
    }
    catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}


//int main(int argc, char **argv)
//{
  //CLI *args = parse(argc, argv);
  //auto filename = *(split(std::string(args->infile), '/').end()-1);

  // Instanciação do objeto do problema do clique máximo com pesos nos vértices.
  // A instância da classe MWCProblem possui a matriz de adjacências do grafo
  // e os pesos correspondentes aos vértices, assim como os métodos que lidarão
  // diretamente com os cromossomos, como o reparo de solução e a função
  // objetivo.
  //MWCProblem mwcp(args->infile);
  // std::cout << "Matrix inicializada: arquivo " << filename << std::endl;

  //TimeGAFactory gaFactory(mwcp);
 
  // Geração da população inicial
  //auto pop = mwcp.init_pop(args->pop_size, 0.25);
  //mwcp.eval(pop);

  // Avaliando população inicial
  // Define a instância da classe de Algoritmo genético
  //GeneticAlgorithm ga = gaFactory.make_ga(args->tour_size, 
  //    args->epochs, args->crossover_id, args->crossover_rate,
  //    args->mutation_rate);

  // Execução da evolução
  //auto start_point = system_clock::now();
  //ga(pop);
  //auto durationNs = system_clock::now() - start_point; // Duração em nanosegundos
  //auto durationMs = duration_cast<milliseconds>(durationNs);

  //std::cout <<"GA execution time: " << durationMs.count() <<" ms" << std::endl;

  // Solução final
  //Chrom melhor = pop.best_element();
  //unsigned int finalcost = (uint) melhor.fitness();
  //std::cout << "Clique weight: " << finalcost << std::endl;

  // Iterações pelo cromossomo pegando os índices dos genes '1' para definir
  // os vértices que fazem parte da solução final encontrada
  //std::vector<int> solution;
  //std::cout << "Nodes:\n";
  //for (size_t i = 0; i < melhor.size(); i++) {
  //  if (melhor[i]) {
  //    solution.push_back(i+1);
  //    std::cout << i+1 << " ";
  //  }
  //}
  //std::cout << std::endl;

  //if (args->using_db) {
    // Configura a tabela
    //MCPModel execution(args);
    //execution.instance_file = filename;
    //execution.duration_in_ms = durationMs.count();
    //const std::vector<Chrom>& conv = ga.get_convergence();
    //execution.set_convergence(conv);
    //execution.solution_size = std::accumulate(melhor.begin(), melhor.end(), 0);
    //execution.solution = MCPModel::sequence_to_string<int>(solution);
    //execution.total_cost = (int) finalcost;

    // Conecta com o banco
    //db::Database db(args->databasefile);
    //db.set_model(&execution);
    //db.exec_insertion();
  //}
  //return 0;
//}

