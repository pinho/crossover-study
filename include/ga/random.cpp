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