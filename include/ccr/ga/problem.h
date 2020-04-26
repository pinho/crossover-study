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

	virtual double objective_function(Enc& chromosome) = 0;
	virtual std::string name() = 0;
	virtual std::string sigle() = 0;

protected:
	uint chromSize;
	std::ifstream infile;
};

#endif //CROSSOVERRESEARCH_PROBLEM_H
