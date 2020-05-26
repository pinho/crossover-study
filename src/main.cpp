#include <iostream>
#include <chrono>
#include <algorithm>
#include <ga/encoding.h>
#include <ga/crossover_fabric.h>
#include <ga/genetic_algorithm.h>
#include <cli/parse.h>
#include <db/database_entry.hpp>
// ParadisEO
#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
// VSQLite++
#include <sqlite/connection.hpp>
#include <sqlite/database_exception.hpp>

#include "scp/set_covering_problem.h"
#include "scp/solution.h"
#include "mcp/maximum_clique_problem.h"
#include "mcp/solution.h"
#include "mkp/m_knapsack_problem.h"


/**
 * Função executada dentro de cada geração do algoritmo.
 * Usada para efetuar alguma operação com a população durate a evolução.
 */
void __gaCallback(int gen, eoPop<Chrom> &pop) {
    Chrom::Fitness __f = pop.best_element().fitness();
    std::cout << gen << "a geração --- Melhor fitness: " << __f
              << std::endl;
}


/**
 * Escreve todos os dados na tabela do arquivo .db
 */
void write_into_db(Problem &problem, cl_arguments &args) {

}


/**
 * Definição e execução do Algoritmo Genético e armazenamento do dados
 * no banco SQLite;
 */
void exec_algorithm(Problem &problem, cl_arguments &arg) {
    using namespace std::chrono;

    // Criação da população inicial e avaliação da mesma usando o
    // objeto da classe Problem
    auto population = problem.init_pop( arg.pop_size );
    problem.eval(population);

    // Definição da configuração do Algoritmo Genético:
    // Operadores de seleção, mutação e o critério de parada (continuador)
    eoDetTournamentSelect<Chrom> select(8);
    eoBitMutation<Chrom> mutation(arg.mutation_rate);
    eoGenContinue<Chrom> continuator(arg.epochs);

    // Definição do operador de crossover
    eoQuadOp<Chrom> *crossover_ptr = CrossoverFabric::create(arg.crossover_id);
    auto crossover_name = CrossoverFabric::name(arg.crossover_id);

    // Instanciação do objeto do algoritmo genético
    GeneticAlgorithm ga(problem, select, *crossover_ptr, arg.crossover_rate,
            mutation, 1, continuator);

    // Vector de cromossomos, usado para armazenar a convergência da execução
    std::vector<Chrom> converg;

    // Execução do processo de evolução da população inicial
    // E armazenamento de tempo (time_points) pro cálculo do tempo de execução.
    auto t0 = system_clock::now();
    ga(population, converg, __gaCallback);
    auto dur = system_clock::now() - t0;

    // Tratamento da população final
    write_into_db(problem, arg);
}

//------------------------------------------------------------------------------
// Função main
//------------------------------------------------------------------------------

int main(int argc, char **argv) {
    auto cli = parse(argc, argv);

    try {
        
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}