#include "problem.h"

size_t Problem::get_chromsize() {
    return __chromSize;
}

void Problem::eval(Chrom& chromosome) {
    if (chromosome.invalid())
        chromosome.fitness( this->__evalFunction(chromosome) );
}

void Problem::eval(eoPop<Chrom>& pop) {
    for (uint i=0; i < pop.size(); i++) {
        this->eval(pop[i]);
#ifndef DEBUG
    }
#else
        std::cout << "\r" << i+1 << " de " << pop.size()
            << " indivíduos avaliados" << std::flush;
    }
    std::cout << std::endl;
#endif
}

eoEvalFunc<Chrom>& Problem::get_eval_function() {
  return this->__evalFunction;
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
