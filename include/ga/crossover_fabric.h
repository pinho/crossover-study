//
// Created by ronaldd on 23/04/2020.
//

#ifndef CROSSOVERRESEARCH_CROSSOVER_FABRIC_H
#define CROSSOVERRESEARCH_CROSSOVER_FABRIC_H

#include "encoding.h"
#include <paradiseo/eo/ga/eoBitOp.h>

class CrossoverFabric {
public:
	static eoQuadOp<Chrom> *create(uint crossID);
	static eoQuadOp<Chrom> *create_uniform(double bias = 0.5);
	static eoQuadOp<Chrom> *create_cutpoints(uint numPoints);
};

#endif //CROSSOVERRESEARCH_CROSSOVER_FABRIC_H
