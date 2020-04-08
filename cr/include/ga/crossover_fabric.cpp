//
// Created by ronaldd on 07/04/2020.
//

#include "crossover_fabric.h"

eoQuadOp<chromosome> *cr::crossover_fabric::create_uniform (double bias = 0.5) {
  return new eoUBitXover<chromosome>(bias);
}

eoQuadOp<chromosome> *cr::crossover_fabric::create_cutpoints (uint num) {
  if (num == 0) {
    throw std::invalid_argument("Can't create a 0-points crossover!");
  } else if (num == 1) {
    return new eo1PtBitXover<chromosome>();
  } else {
    return new eoNPtsBitXover<chromosome>(num);
  }
}

eoQuadOp<chromosome> * cr::crossover_fabric::create (uint crossID) {
  if (crossID == 0) {
    return create_uniform();
  } else {
    return create_cutpoints(crossID);
  }
}
