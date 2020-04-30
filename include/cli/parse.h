#ifndef CROSSOVERRESEARCH_PARSE_H
#define CROSSOVERRESEARCH_PARSE_H

#include <string>
#include "options.h"

/**
 * Mostra o menu de ajuda das opções de linha de comandos
 */
void show_help(int argc, char **argv) {
    printf("Use: %s -f [INPUTFILE] [ARGS] ...\n\n", argv[0]);
    printf("ARGS:\n\n");
    for (unsigned int i = 0; i < NUM_OPTIONS; i++) {
        if (long_options[i].name) {
            printf(" -%c, --%-10s  %s\n", long_options[i].val, long_options[i].name, DESC[i]);
        }
    }
}

/**
 * Anaçisar os argumentos passados por linha de comando
 */
cl_arguments *parse(int argc, char **argv)
{
    auto res = new cl_arguments();
    int opt;

    while ((opt = getopt_long(argc,argv, short_options,long_options,0)) != -1) {
        switch (opt) {
            case 'f':
                if (optarg) res->infile = optarg;
                break;
            case 'p':
                if (optarg) res->pop_size = std::stoi(optarg);
                break;
            case 'g':
                if (optarg) res->epochs = std::stoi(optarg);
                break;
            case 'c':
                if (optarg) res->crossover_rate = std::stod(optarg);
                break;
            case 'm':
                if (optarg) res->mutation_rate = std::stod(optarg);
                break;
            case 'x':
                if (optarg) res->crossover_id = std::stoi(optarg);
                break;
            case 'h':
                show_help(argc, argv);
                exit(127);
            default:
                printf("Use -h ou --help para ver as opções de linha de comandos.\n");
                exit(2);
        }
    }

    return res;
}

std::ostream& operator << (std::ostream& os, cl_arguments& cli) {
    const char *params = "[PARAM]";
    std::string cross_name =
            cli.crossover_id == 0? "Uniforme" : std::to_string(cli.crossover_id).append("-Pontos");

    os << params << " Tamanho da população: " << cli.pop_size << "\n";
    os << params << " Número de gerações: " << cli.epochs << "\n";
    os << params << " Operador de crossover: " << cross_name << "\n";
    os << params << " Taxa de cruzamento: " << cli.crossover_rate*100 << "%\n";
    os << params << " Taxa de mutação: " << cli.mutation_rate*100 << "%\n";

    return os;
}

/**
 * TODO: Criar uma função que define uma string ID para combinação de parametros
 * Exemplo:
 * -- popsize = 100, epochs = 100, crossover_rate = 0.8, mutacao = 0.05, crossover uniforme
 * -- = UNIFORMP100G100CR080MR005
 */
std::string identify(cl_arguments& cli);

#endif//CROSSOVERRESEARCH_PARSE_H