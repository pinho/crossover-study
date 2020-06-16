#include "random.h"

// Gerador de valores booleanos aleatórios (usado nas implementações de Random)
eoBooleanGenerator BOOLRNG;

template <>
Chrom Random<Chrom>::uniform_chromosome (uint csize) {
    eoInitFixedLength<Chrom> _init(csize, BOOLRNG);
    Chrom x; _init(x);
    return x;
}

template <>
eoPop<Chrom> Random<Chrom>::population(uint chromsize, uint popsize) {
    eoInitFixedLength<Chrom> _init(chromsize, BOOLRNG);
    return eoPop<Chrom>(popsize, _init);
}

template <>
std::pair<int, int> Random<Chrom>::choice(std::vector<int>& container) {
    eoUniformGenerator<int> rng(0, container.size());
    int r = rng();
    return std::pair<int, int>(r, container[r]);
}