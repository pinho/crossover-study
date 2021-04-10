#include "problem.h"

size_t Problem::get_chromsize() {
    return this->chromSize;
}

void Problem::eval(Chrom& chromosome) {
  this->operator()(chromosome);
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

bool Problem::is_minimization() {
    return this->minimization;
}
