//
// Created by ronaldd on 07/04/2020.
//

#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_

#include <paradiseo/eo/eoAlgo.h>

#include "chromosome.h"

class genetic_algorithm : public eoAlgo<chromosome> {
public:
    genetic_algorithm();
};

#endif //_GENETIC_ALGORITHM_H_
