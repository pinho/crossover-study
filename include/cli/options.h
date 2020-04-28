#ifndef CROSSOVERRESEARCH_OPTIONS_H
#define CROSSOVERRESEARCH_OPTIONS_H

#include <getopt.h>

#ifdef __cpluscplus
extern "C" {
#endif

// TODO: IMplementar struct para conjunto de argumentos
struct cl_arguments {
    char *infile = (char *) "";
    unsigned int pop_size = 8;
    unsigned int epochs = 50;
    double crossover_rate = 0.0;
    double mutation_rate = 0.0;
};

option long_options[] = {
    {"ifile", required_argument, 0, 'f'},
    {"popsize", required_argument, 0, 'p'},
    {"epochs", required_argument, 0, 'g'},
    {"xrate", required_argument, 0, 'x'},
    {"mrate", required_argument, 0, 'm'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

const char *short_options = "f:p:g:x:m:h";

const unsigned int NUM_OPTIONS = 6;

#ifdef __cpluscplus
}
#endif

#endif // CROSSOVERRESEARCH_OPTIONS_H