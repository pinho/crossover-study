#ifndef CROSSOVERRESEARCH_DATABASE_ENTRY_HPP
#define CROSSOVERRESEARCH_DATABASE_ENTRY_HPP

#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>

/**
 * DatabaseEntry mapeia a tabela do banco de dados SQLite e encapsula o método
 * de escrita de dados na tabela 
 * */
class DatabaseEntry {
public:
    /**
     * Default DatabaseEntry constructor.
     * @param problem,
     * @param problem_sigle,
     * @param instance,
     * @param crossover,
     * @param crossing_rate,
     * @param popsize,
     * @param num_epochs,
     * @param best_solution, 
     * @param conv,
     * @param dur,
     */
    DatabaseEntry(const char *problem, const char *problem_sigle, std::string instance,
            const char *crossover, const float crossing_rate, int popsize,
            int num_epochs, double best_solution, std::vector<double> &conv,
            std::chrono::system_clock::duration &dur);

    /**
     * Escreve os dados do objetochar * no banco de dados SQLite.
     * @param con, instância da conexão com o banco de dados.
     */
    void write(sqlite::connection &con);

    /**
     * Define o código de parâmetro a partir dos dados:
     * ~Nome do crossover
     * ~Taxa de cruzamento
     * ~Tamanho de população
     * ~Número de gerações
     */
    std::string conf_code();

private:
    const char *__problem, *__problem_acronym, *__crossover;
    std::string __instance;
    const float __cross_rate;
    int __pop_length;
    int __num_epochs;
    double __best_solution;
    std::vector<double> &__conv;
    std::chrono::system_clock::duration &__duration;
};

#endif