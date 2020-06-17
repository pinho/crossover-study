#ifndef CROSSOVERRESEARCH_PARSE_H
#define CROSSOVERRESEARCH_PARSE_H

#include "options.h"
#include <cstdio>

/**
 * Mostra o menu de ajuda das opções de linha de comandos
 */
void show_help(char **argv) {
    printf("Use: %s -f [input-file] [ARGS] ...\n", argv[0]);
    
    printf("ARGS:\n");
    for (unsigned int i = 0; i < NUM_OPTIONS; i++) {
        if (long_options[i].name) {
            if (long_options[i].val) {
                printf("  -%c, --%-10s  %s\n", long_options[i].val, long_options[i].name, DESC[i]);
            } else {
                printf("      --%-10s  %s\n", long_options[i].name, DESC[i]);
            }
        }
    }
}

/**
 * Anaçisar os argumentos passados por linha de comando
 */
CLI *parse(int argc, char **argv)
{
    auto res = new CLI();
    int opt;

    while ((opt = getopt_long(argc,argv, short_options,long_options,0)) != -1) {
        switch (opt) {
            case 'd':
                if (optarg) {
                    res->databasefile = optarg;
                    res->using_db = true;
                }
                break;
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
            case 'r':
                if (optarg) res->tour_size = std::stoi(optarg);
                break;
            case 'h':
                show_help(argv);
                exit(127);
            default:
                printf("Use -h ou --help para ver as opções de linha de comandos.\n");
                exit(2);
        }
    }

    return res;
}

/**
 * Define uma string ID para cada cominação de parâmetros
 */
std::string identify(CLI& cli) {
    std::string ID;

    if (cli.crossover_rate > 1 || cli.crossover_rate < 0) {
        cli.crossover_rate = 1;
    }

    if (cli.mutation_rate > 1 || cli.mutation_rate < 0) {
        cli.mutation_rate = 0.05;
    }

    ID = cli.crossover_id == 0? "UNIFORM" : std::to_string(cli.crossover_id).append("POINTS");
    // P(popsize)
    ID.append("P").append(std::to_string(cli.pop_size));
    // G(epochs)
    ID.append("G").append(std::to_string(cli.epochs));
    // CR(crossover_rate)
    ID.append("CR");
    auto cr = std::to_string(cli.crossover_rate);
    cr.erase(cr.begin()+1);
    cr.erase(cr.begin()+3, cr.end());
    ID.append(cr);
    // MR(mutation_rate)
    ID.append("MR");
    auto mr = std::to_string(cli.mutation_rate);
    mr.erase(mr.begin()+1);
    mr.erase(mr.begin()+3, mr.end());
    ID.append(mr);


    return ID;
}

#endif//CROSSOVERRESEARCH_PARSE_H