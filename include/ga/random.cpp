#include "encoding.h"
#include "random.h"

template <>
Chrom Random<Chrom>::uniform_chromosome (uint csize) {
    eoBooleanGenerator _gen;
    eoInitFixedLength<Chrom> _init(csize, _gen);
    Chrom x; _init(x);
    return x;
}