//
// Created by ronaldd on 23/04/2020.
//

#ifndef CROSSOVERRESEARCH_ENCODING_H
#define CROSSOVERRESEARCH_ENCODING_H

#include <paradiseo/eo/ga/eoBit.h>
#include <paradiseo/eo/eoPop.h>

typedef double fitness_t;
typedef eoBit<fitness_t> Chrom;
typedef eoPop<Chrom> Population;

#endif //CROSSOVERRESEARCH_ENCODING_H
