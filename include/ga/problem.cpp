#include "problem.h"

uint Problem::get_chromsize() {
    return __chromSize;
}

void Problem::eval(Chrom& chromosome) {
    if (chromosome.invalid())
        chromosome.fitness( this->objective_function(chromosome) );
}

void Problem::eval(eoPop<Chrom>& pop) {
    for (Chrom& chrom : pop) {
        this->eval(chrom);
    }
}
