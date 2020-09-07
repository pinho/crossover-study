#ifndef CROSSOVERRESEARCH_ENTROPY_H
#define CROSSOVERRESEARCH_ENTROPY_H

#include <vector>
#include <cmath>
#include <numeric>
#include "encoding.h"

class Entropy {
public:
  static std::vector<double> allele_vector(const Population& pop);
  static double overall(const Population& pop);
};

#endif