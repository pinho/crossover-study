#include "problem.h"

uint Problem::get_chromsize() {
    return __chromSize;
}

void Problem::eval(Chrom& chromosome) {
    if (chromosome.invalid())
        chromosome.fitness( this->objective_function(chromosome) );
}

void Problem::eval(eoPop<Chrom>& pop) {
    for (uint i=0; i < pop.size(); i++) {
        this->eval(pop[i]);
#ifndef NDEBUG
    }
#else
        std::cout << "\r" << i+1 << " de " << pop.size()
            << " indivíduos avaliados" << std::flush;
    }
    std::cout << std::endl;
#endif
}

const char *Problem::name() {
    return this->__name;
}

const char *Problem::acronym() {
    return this->__acronym;
}

bool Problem::is_minimization() {
    return this->__minimize;
}
