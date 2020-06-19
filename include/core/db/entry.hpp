#ifndef CORE_DATABASE_ENTRY_HPP
#define CORE_DATABASE_ENTRY_HPP

#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include "../ga/problem.h"
#include "../ga/encoding.h"
#include "../ga/crossover_fabric.h"
#include "../cli/options.h"
#include "modes.hpp"

using namespace sqlite;

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
void db_entry(connection& con, db_structure mode, CLI *args, int clique_size) {
    std::string sql;

    //-------------------------------
    // Problema do Clique Máximo
    //-------------------------------
    if (mode == db_structure::mc) {
        // TODO: Adicionar os outros valores no banco
        sql += "INSERT INTO execucoes_mc (";
        sql += "pop_length, num_gen, cross_rate, mutation_rate, crossover, ";
        sql += "solution_size";
        sql += ") VALUES (?, ?, ?, ?, ?, ?);";

        // Nome do operador de crossover
        auto cn = CrossoverFabric::name(args->crossover_id);

        execute ins(con, sql);
        ins % (int) args->pop_size
            % (int) args->epochs
            % (double) args->crossover_rate
            % (double) args->mutation_rate
            % cn // nome do crossover
            % clique_size;
            // TODO: Convergência, duração, solução, arquivo
        ins();
    }
}


#endif