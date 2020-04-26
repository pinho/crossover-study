#ifndef CROSSOVERRESEARCH_PROBLEM_H
#define CROSSOVERRESEARCH_PROBLEM_H

#include <fstream>
#include "encoding.h"

// TODO: Verificar e finalizar a classe virtual para problemas

template <class Enc = Chrom>
class Problem {
public:
	using F = Chrom::Fitness;

	~Problem() = default;

	uint get_chromsize();
	void eval(Enc &chromosome);
	void eval(eoPop<Enc> &pop);

	virtual F objective_function(Enc& chromosome) = 0;

protected:
	uint __chromSize;
	char *__infilename;
	const char *__name, *__acronym;
};

#endif //CROSSOVERRESEARCH_PROBLEM_H
