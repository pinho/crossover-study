#include "problem.h"

template <class E> Problem<E>::~Problem() = default;

template <class E>
uint Problem<E>::get_chromsize() {
    return __chromSize;
}

template <class E>
void Problem<E>::eval(E& chromosome) {
    if (chromosome.invalid())
        chromosome.fitness( this->objective_function(chromosome) );
}

template <class E>
void Problem<E>::eval(eoPop<E>& pop) {
    for (auto& chrom : pop) {
        this->eval(chrom);
    }
}
