//
// Created by ronaldd on 23/04/2020.
//

#include "problem.h"

template <class E>
uint Problem<E>::get_chromsize() {
	return this->__chromSize;
}

template <class E>
void Problem<E>::eval(E& chrom) {
	if (chrom.invalid()) {
		chrom.fitness( objective_function(chrom) );
	}
}

template <class E>
void Problem<E>::eval(eoPop<E>& pop) {
	for (auto &chrom : pop) {
		eval(chrom);
	}
}