#include "database_entry.hpp"

using namespace std::chrono;

DatabaseEntry::DatabaseEntry(const char *problem, const char *problem_sigle,
        std::string instance, const char *crossover, const float crossing_rate, 
        int popsize, int num_epochs, double best_solution, 
        std::vector<double> &conv, std::chrono::system_clock::duration &dur)
        : __problem(problem),
        __problem_acronym(problem_sigle),
        __crossover(crossover),
        __instance(instance),
        __cross_rate(crossing_rate),
        __pop_length(popsize),
        __num_epochs(num_epochs),
        __best_solution(best_solution),
        __conv(conv),
        __duration(dur) {}

std::string DatabaseEntry::conf_code() {
    std::string res(__crossover);
    res += "-";
    res += std::to_string( int(100*__cross_rate) );
    res += "-";
    res += "P";
    res += std::to_string(__pop_length);
    res += "-";
    res += "G";
    res += std::to_string(__num_epochs);
    return res;
}
    
void DatabaseEntry::write (sqlite::connection &con) {
    std::string query = "INSERT INTO execucoes ";
    query += "(config_code, crossover, convergencia, melhor_solucao, tempo_ag, instancia, problema, sigla_problema, tam_populacao, num_geracoes, taxa_cruzamento) ";
    query += "VALUES (?,?,?,?,?,?,?,?,?,?,?);";

    sqlite::execute ins(con, query);

    std::stringstream ss;
    for (auto it = __conv.cbegin(); it != __conv.cend(); ++it) {
        ss << *it;
        if (it+1 != __conv.cend())
            ss << ";";
    }

    auto config_code = this->conf_code();
    auto count = duration_cast<milliseconds>(__duration).count();

    ins % config_code % __crossover % ss.str() % __best_solution % count % __instance % __problem % __problem_acronym % __pop_length % __num_epochs % __cross_rate;
    ins();
}
    