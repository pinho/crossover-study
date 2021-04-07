//
// Created by ronaldd on 23/04/2020.
//

#ifndef CROSSOVERRESEARCH_ENCODING_H
#define CROSSOVERRESEARCH_ENCODING_H

#include <paradiseo/eo/ga/eoBit.h>
#include <paradiseo/eo/eoPop.h>

// #ifdef DEF_FITNESS_TYPE
// Tipo do fitness definido em tempo de compilação
//   typedef fitness_t DEF_FITNESS_TYPE
// #else
//   typedef double fitness_t;
// #endif

// Define o tipo de um cromossomo
typedef eoBit<double> Chrom;

// Define o tipo da população de cromossomos
typedef eoPop<Chrom> Population;

#endif //CROSSOVERRESEARCH_ENCODING_H
