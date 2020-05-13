#include <algorithm>
#include "database_entry.hpp"

DatabaseEntry::DatabaseEntry (std::string config_code, std::string crossover,
        std::string instance, float best_solution,
        std::vector<double> &convergence,
        std::chrono::system_clock::duration &ga_duration)
        : __config_code(config_code), __crossover(crossover), 
        __instance(instance), __best_solution(best_solution), 
        __convergence(convergence), __duration(ga_duration) {}

    
void DatabaseEntry::write (sqlite::connection &con) {
    std::stringstream sql;
    sql << "INSERT INTO execucoes ";
    sql << "(config_code, crossover, convergencia, melhor_solucao, tempo_ag, instancia) ";
    sql << "VALUES (?, ?, ?, ?, ?, ?);";
    std::string insert_into = sql.str();

    std::stringstream ssConv;
    auto it = __convergence.cbegin();
    for (; it != __convergence.cend(); ++it) {
        ssConv << *it;
        if (it+1 != __convergence.cend())
            ssConv << ';';
    }

    sqlite::execute ins(con, insert_into);
    ins % __config_code % __crossover % ssConv.str() % __best_solution % (double)__duration.count() % __instance;

    ins();
}
    