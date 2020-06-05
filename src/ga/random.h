#ifndef CROSSOVERRESEARCH_RANDOM_H
#define CROSSOVERRESEARCH_RANDOM_H

#include <algorithm>
#include <paradiseo/eo/utils/eoRndGenerators.h>
#include <paradiseo/eo/eoPop.h>
#include "encoding.h"

template <class Encoding> class Random {
public:
    /**
     * Function used to generate a chromosome instance
     * using uniform distribution */
    static Encoding uniform_chromosome(uint chromsize);

    /**
     * Function used to initialize a population of chromosomes randomly */
    static eoPop<Encoding> population(uint chromsize, uint popsize);

    /**
     * Choice an element randomly from a container
     * Returns a pair with the index and the element chosen */
    static std::pair<int, int> choice(std::vector<int>& container);
};

#endif//CROSSOVERRESEARCH_RANDOM_H