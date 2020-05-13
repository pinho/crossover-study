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
 * de escrita de dados na tabela */
class DatabaseEntry {
public:
    /**
     * Default DatabaseEntry constructor.
     * @param config_code, string_id da combinação de parâmetros
     * @param crossover, nome do operador de crossover
     * @param instance, nome do arquivo de instância usado
     * @param best_solution, solução encontrada pelo AG nessa execução
     * @param convergence, referência p/ um vector com os dados da convergência
     * @param ga_duration, referência p/duração da execução do operador de AG
     */
    DatabaseEntry(std::string config_code, std::string crossover, std::string instance,
            float best_solution, std::vector<double> &convergence,
            std::chrono::system_clock::duration &ga_duration);

    /**
     * Escreve os dados do objetochar * no banco de dados SQLite.
     * @param con, instância da conexão com o banco de dados.
     */
    void write(sqlite::connection &con);

private:
    std::string __config_code, __crossover, __instance;
    float __best_solution;
    std::vector<double>& __convergence;
    std::chrono::system_clock::duration __duration;
};

#endif