#ifndef CROSSOVERRESEARCH_PARSE_H
#define CROSSOVERRESEARCH_PARSE_H

#include <string>
#include "options.h"

/**
 * Mostra o menu de ajuda das opções de linha de comandos
 * TODO: Implementar e formatar
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

#endif//CROSSOVERRESEARCH_PARSE_H