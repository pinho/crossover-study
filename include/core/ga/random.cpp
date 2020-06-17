#include "random.h"

// Gerador de valores booleanos aleatórios (usado nas implementações de Random)

template <>
Chrom Random<Chrom>::uniform_chromosome (uint csize, double bias) {
    eoBooleanGenerator boolRng(bias);
    eoInitFixedLength<Chrom> _init(csize, boolRng);
    Chrom x; _init(x);
    return x;
}

template <>
eoPop<Chrom> Random<Chrom>::population(uint chromsize, uint popsize, double bias) {
    eoBooleanGenerator boolRng(bias);
    eoInitFixedLength<Chrom> _init(chromsize, boolRng);
    return eoPop<Chrom>(popsize, _init);
}

template <>
std::pair<int, int> Random<Chrom>::choice(std::vector<int>& container) {
    eoUniformGenerator<int> rng(0, container.size());
    int r = rng();
    return std::pair<int, int>(r, container[r]);
}

template <>
double Random<Chrom>::uniform(double min, double max) {
    eoUniformGenerator<double> gen(min, max);
    return gen();
}
