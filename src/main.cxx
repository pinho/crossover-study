#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ga/encoding.h>
#include <ga/crossover_fabric.h>
#include <ga/genetic_algorithm.h>
#include <cli/parse.h>
#include <db/database_entry.hpp>
#include <io/utils.h>
#include <paradiseo/eo/ga/eoBitOp.h>
#include <paradiseo/eo/eoGenContinue.h>
#include <paradiseo/eo/eoDetTournamentSelect.h>
#include <sqlite/connection.hpp>
#include <sqlite/database_exception.hpp>

#include "problem_fabric.h"
#include "version.h"

#ifdef _WIN32
# define __path_sep '\\'
#elif __unix__
# define __path_sep '/'
#elif __linux__
# define __path_sep '/'
#elif __APPLE__
# define __path_sep '/'
#endif
 
/**
 * Cortar o caminho do arquivo de instância
 */
std::string cut_instance_path(std::string fullpath) {
    auto vec = split(fullpath, __path_sep);
    return vec[vec.size()-1];
}

/**
 * Imprimir traços para separar linhas no console
 */
void sep_line(const uint ndashes = 80) {
    for (uint i=0; i < ndashes; i++)
        std::cout << "-" << std::flush;
    std::cout << std::endl;
}

bool MINIMIZE;

/**
 * Função executada dentro de cada geração do algoritmo.
 * Usada para efetuar alguma operação com a população durate a evolução.
 */
void __gaCallback(int gen, eoPop<Chrom> &pop) {
    Chrom chrom = pop.best_element();
    double _fitness;
    if (MINIMIZE) {
        _fitness = 1/chrom.fitness();
    } else {
        _fitness = chrom.fitness();
    }
   #ifdef __unix__
    std::cout << "\e[48;5;88m ";
   #endif
    std::cout << "G" << gen << ": Fittest: " << _fitness << std::flush;
   #ifdef __unix__
    std::cout << " \e[0m";
   #endif
    std::cout << std::endl;
}


/**
 * Calcular a entropia de uma população.
 * O cálculo é feito para cada gene em um vector onde cada posição representa
 * a entropia em uma posição do cromossomo e em seguida é retornada a média
 * desse vector. */
// double entropy_average(const eoPop<Chrom> &pop) {
//     const int SIZE = pop.size();
// }
 


/**
 * Definição e execução do Algoritmo Genético e armazenamento do dados
 * no banco SQLite;
 */
void exec_algorithm(Problem &problem, cl_arguments &arg) {
    using namespace std::chrono;

    std::string filename = cut_instance_path(arg.infile);
    std::cout << "Arquivo de instância: " << filename << std::endl;
    sep_line();

    // Criação da população inicial e avaliação da mesma usando o
    // objeto da classe Problem
    std::cout << "Inicializando população ... " << std::flush;
    auto population = problem.init_pop( arg.pop_size );
    std::cout << "OK" << std::endl;

    std::cout << "Avaliando população inicial ... " << std::flush;
    problem.eval(population);
    std::cout << "OK" << std::endl;

    // Definição da configuração do Algoritmo Genético:
    // Operadores de seleção, mutação e o critério de parada (continuador)
    eoDetTournamentSelect<Chrom> select(arg.tour_size);
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
    // Problem::Solution final_solution;
    Chrom __final = population.best_element();

    // escrever no banco (se definido)
    if (arg.using_db) {
        auto instanceFile = cut_instance_path(arg.infile);
        DatabaseEntry entry(&problem, instanceFile, crossover_name, &arg,
                __final, &converg, dur);
        try {
            sqlite::connection con(arg.databasefile);
            entry.write(con);
            std::cout << "Dados escritos em " << arg.databasefile << std::endl;
        }
        catch (sqlite::database_exception &e) {
            std::cerr << "Database Exception: " << e.what() << std::endl;
        }
    }
}

//------------------------------------------------------------------------------
// Função main
//------------------------------------------------------------------------------

int main(int argc, char **argv) {
    using namespace std;

    // Verifica se foi paasado algum argumento
    if (argc < 2) {
        std::cout << "Faltando argumentos: ";
        std::cout << "Use " << argv[0] << " --help" << std::endl;
        return 1;
    }
    if (string(argv[1]).compare("--version") == 0) {
        std::cout << argv[0] << " v" << VERSION << std::endl;
        return 0;
    }

    // transformando argumentos em um vector
    vector<char *> vec_args;
    for (int i=0; i < argc; i++) {
        vec_args.push_back( argv[i] );
    }

    // pegando somente o primeiro argumento após o nome do programa
    string problem_name = vec_args[1];
    vec_args.erase(vec_args.begin()+1);
    char **newArgs = &vec_args[0];

    try {
        auto cli = parse(argc, newArgs);

        // Criando uma instância de um problema
        auto prob = ProblemFabric::create( cli->infile, problem_name );
        MINIMIZE = prob->is_minimization();
        
        cout << prob->name() << ": " << flush;
        if (MINIMIZE) cout << "Minimização" << endl;
        else cout << "Maximização" << endl;

        // Usa o objeto problem e interface de linha de comandos para
        // criar e executar o algoritmo genético
        exec_algorithm(*prob, *cli);
    }
    catch (std::runtime_error &err) {
        std::cout << "Erro em tempo de execução: " << err.what() << std::endl;
        return 1;
    }
    catch (std::logic_error &err) {
        std::cout << "Erro de lógica: " << err.what() << std::endl;
        return 1;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}