#ifndef CROSSOVERRESEARCH_DATABASE_ENTRY_HPP
#define CROSSOVERRESEARCH_DATABASE_ENTRY_HPP

#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include "ga/problem.h"
#include "ga/encoding.h"
#include "cli/options.h"

/**
 * @class DatabaseEntry
 * 
 * DatabaseEntry mapeia a tabela do banco de dados SQLite e encapsula o método
 * de escrita de dados na tabela 
 * */
class DatabaseEntry {
public:
    /**
     * Default DatabaseEntry constructor.
     * @param problem, objeto de problema usado
     * @param instance, nome do arquivo de instância do problema
     * @param crossover, nome do operador de crossover
     * @param args, objeto de estrutura de argumentos de linha de comandos
     * @param best_solution, melhor fitness ao fim da execução
     * @param conv, vector de fitnesses com a convergencia do AG
     * @param dur, tempo de execução do Algoritmo Genético
     */
    DatabaseEntry(Problem *problem, std::string instance, std::string crossover,
            cl_arguments *args, Chrom &best_solution, std::vector<Chrom> *const conv,
            std::chrono::system_clock::duration &dur)
            : __problem(problem), __instance(instance), __crossover(crossover),
              __cli(args), __best_solution(best_solution), __conv(conv),
              __duration(dur)
    {
        if (std::string("SCP").compare(problem->acronym()) == 0) {
            this->is_max = false;
        } else if (std::string("MCP").compare(problem->acronym()) == 0) {
            this->is_max = true;
        } else if (std::string("MKP").compare(problem->acronym()) == 0) {
            this->is_max = true;
        } else if (std::string("STP").compare(problem->acronym()) == 0) {
            this->is_max = false;
        }
    }

    /**
     * Define um código em string que define vários parâmetros da configuração
     */
    std::string conf_code() {
        std::string res(this->__crossover);
        res += "-";
        res += std::to_string( int(100*__cli->crossover_rate) );
        res += "-";
        res += "P";
        res += std::to_string(__cli->pop_size);
        res += "-";
        res += "G";
        res += std::to_string(__cli->epochs);
        return res;
    }


    /**
     * Escreve os dados do objeto no banco de dados SQLite.
     * @param con, instância da conexão com o banco de dados.
     */
    void write(sqlite::connection &con) {
        using namespace std::chrono;

        std::string query = "INSERT INTO execucoes ";
        query += "(config_code, crossover, convergencia, melhor_solucao, tempo_ag, instancia, problema, sigla_problema, tam_populacao, num_geracoes, taxa_cruzamento) ";
        query += "VALUES (?,?,?,?,?,?,?,?,?,?,?);";

        sqlite::execute ins(con, query);

        std::stringstream ss;
        for (auto it = __conv->cbegin(); it != __conv->cend(); ++it) {
            if (is_max) ss << it->fitness();
            else ss << (1 / it->fitness());
            if (it+1 != __conv->cend()) ss << ";";
        }
        auto count = duration_cast<milliseconds>(__duration).count();
        std::string cc = this->conf_code();
        double best = is_max ? double(__best_solution.fitness()) : double(1/__best_solution.fitness());

        ins % cc % __crossover % ss.str() % best % count % __instance % __problem->name() % __problem->acronym() % int(__cli->pop_size) % int(__cli->epochs) % __cli->crossover_rate;
        ins();
    }

private:
    Problem *__problem;
    std::string __instance, __crossover;
    cl_arguments *__cli;
    Chrom &__best_solution;
    std::vector<Chrom> *__conv;
    std::chrono::system_clock::duration &__duration;
    bool is_max;
};

#endif