#ifndef CORE_DATABASE_ENTRY_HPP
#define CORE_DATABASE_ENTRY_HPP

#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include "../ga/problem.h"
#include "../ga/encoding.h"
#include "../ga/crossover_fabric.h"
#include "../cli/options.h"
#include "modes.hpp"

using namespace sqlite;

/**
 * Converte um vector para uma string contendo todos os seus valores
 * separados por vírgula
 */
template <typename T>
std::string sequence_to_string(std::vector<T>& seq) {
    std::stringstream ss;
    auto it = seq.cbegin();
    for (; it != seq.cend(); ++it) {
        ss << *it;
        if ( it != seq.cend()-1 ) {
            ss << ',';
        }
    }
    return ss.str();
}

std::string convergence_to_string(std::vector<Chrom>& c) {
    std::stringstream ss;
    auto it = c.cbegin();
    for (; it != c.cend(); ++it) {
        ss << it->fitness();
        if ( it != c.cend()-1 ) {
            ss << ',';
        }
    }
    return ss.str();
}

/**
 * Escreve dados de um dos problemas em um arquivo de banco de dados
 * A estrutura da tabela é definida pelo argumento "mode"
 * @param con instância de conexão com um arquivo de banco de dados
 * @param mode definição de qual problema está sendo escrito
 * @param args ponteiro para instância de combinação de linha de comandos
 * @param clique_size tamanho clique máximo encontrado
 * @param clque_nodes nós do clique máximo encontrado
 * @param conv convergência da função objetivo durante a evolução
 * @param duration tempo de duração da evolução
 */
void db_entry(connection& con, db_structure mode, CLI *args, int clique_size,
        std::vector<int>& clique_nodes, std::vector<Chrom>& conv,
        std::string file, std::chrono::milliseconds duration) {
    std::string sql;

    //------------------------------------
    // Problema do Clique Máximo
    //------------------------------------
    if (mode == db_structure::mc) {
        sql += "INSERT INTO execucoes_mc (";
        sql += "pop_length, num_gen, cross_rate, mutation_rate, crossover, ";
        sql += "solution_size, solution, convergence, instance_file, duration_ms";
        sql += ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

        // Pré-processamento

        // Nome do operador de crossover
        auto cn = CrossoverFabric::name(args->crossover_id);
        
        // Lista de nós do clique
        std::string nodes = sequence_to_string<int>(clique_nodes);

        // Lista de valores da convergência da evolução
        std::string conv_str = convergence_to_string(conv);

        execute ins(con, sql);
        ins % (int) args->pop_size
            % (int) args->epochs
            % (double) args->crossover_rate
            % (double) args->mutation_rate
            % cn // nome do crossover
            % clique_size
            % nodes
            % conv_str
            % file
            % duration.count();
        ins();
    }
}


#endif