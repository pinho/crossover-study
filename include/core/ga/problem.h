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
//template <typename F> // tipo do valor de fitness
class Problem {
public:
	// Type of the fitness of a chromosome
	using Fitness = typename Chrom::Fitness;

	~Problem() {}

	/**
	 * Getter to private attribute chromSize */
	size_t get_chromsize();

	/**
	 * Getter to member name */
	const char *name();

	/**
	 * Getter to member acronym */
	const char *acronym();

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
   * Returns a reference to EvalFunc object */
  eoEvalFunc<Chrom>& get_eval_function();

	/**
   * Definition of the objective function */
  virtual Fitness operator()(Chrom &chromosome) = 0;

	/**
	 * Show information of the problem instance in a ostream 
	 * std::cout is the default ostream instance */
	virtual void display_info(std::ostream &os) = 0;

	/**
	 * Population initializer
	 * Initialize a population with Encoding and chromSize defined in
	 * problem instance. */
	virtual eoPop<Chrom> init_pop(uint length, double bias) = 0;

	/**
	 * Objective Function
	 * The function that defines the fitness of a chromosome, is the main 
	 * formulation of an optimization problem */
	virtual Fitness objective_function(Chrom &chromosome) = 0;

protected:
	size_t __chromSize; // size of the chromosomes in this problem instance
	char *__infilename; // name of input file of this instance
	char *__name, *__acronym; // name and sigle of the problem
	bool __minimize;
  eoEvalFunc<Chrom> __evalFunction; // Função objetivo
};

#endif //CROSSOVERRESEARCH_PROBLEM_H
