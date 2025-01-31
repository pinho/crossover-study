#ifndef CROSSOVERRESEARCH_PROBLEM_H
#define CROSSOVERRESEARCH_PROBLEM_H

#include <fstream>
#include <paradiseo/eo/eoEvalFunc.h>
#include "encoding.h"

/**
 * classe Problem
 * 
 * Define atributos a caracteristicas de um problema de otimizacao. E' uma
 * classe que possui metodos virtuais a serem implementados em classes filhas
 * (uma classe template para problemas concretos). Herda de eoEvalFunc que
 * fornece mecanismo de execucao da funcao objetivo atraves do metodo operator()
 */
class Problem : public eoEvalFunc<Chrom> {
public:
	// Type of the fitness of a chromosome
	using Fitness = typename Chrom::Fitness;

	~Problem() {
  }

	/**
	 * Getter to private attribute chromSize */
	size_t get_chromsize();

	/**
	 * Check if is a minimization problem */
	bool is_minimization();

  /*
	 * Evaluator of chromosomes.
	 * This method apply the objective function with a chromosome computing
	 * the fitness and set the resultant fitness value to the chromosome. */
	void eval(Chrom &chromosome);

	/**
	 * Apply evaluation to each chromosome in a population */
	void eval(eoPop<Chrom> &pop);

  /**
   * Definition of the objective function */
  void operator()(Chrom& chromosome) = 0;

	/**
	 * Population initializer
	 * Initialize a population with Encoding and chromSize defined in
	 * problem instance. */
	virtual eoPop<Chrom> init_pop(uint length, double bias) = 0;

protected:
	size_t chromSize; // size of the chromosomes in this problem instance
  std::string instanceFilename; // name of input file of this instance
	bool minimization;
  // eoEvalFunc<Chrom> *evalFunction; // Ponteiro para um objeto de função obj.
};

#endif //CROSSOVERRESEARCH_PROBLEM_H
