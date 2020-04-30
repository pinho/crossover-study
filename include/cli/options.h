#ifndef CROSSOVERRESEARCH_OPTIONS_H
#define CROSSOVERRESEARCH_OPTIONS_H

#include <getopt.h>

#ifdef __cpluscplus
extern "C" {
#endif

// TODO: IMplementar struct para conjunto de argumentos
struct cl_arguments {
    char *infile = (char *) "";
    unsigned int pop_size = 100;
    unsigned int epochs = 50;
    unsigned int crossover_id = 0;
    double crossover_rate = 0.8;
    double mutation_rate = 0.05;
};

option long_options[] = {
    {"ifile", required_argument, 0, 'f'},
    {"popsize", required_argument, 0, 'p'},
    {"epochs", required_argument, 0, 'g'},
    {"xrate", required_argument, 0, 'c'},
    {"mrate", required_argument, 0, 'm'},
    {"crossover", required_argument, 0, 'x'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

const char *short_options = "f:p:g:x:m:h";

const unsigned int NUM_OPTIONS = 7;

const char *DESC[NUM_OPTIONS] = {
        "Arquivo de instância do problema",
        "Define o tamanho da população",
        "Define o número de épocas/gerações",
        "Define a taxa de cruzamento (%)",
        "Define a taxa de mutação (%)",
        "Define o operador de crossover utilizado com um ID",
        "Mostra essa lista de opções"
};

#ifdef __cpluscplus
}
#endif

#endif // CROSSOVERRESEARCH_OPTIONS_H