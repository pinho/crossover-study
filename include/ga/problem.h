#ifndef CROSSOVERRESEARCH_PROBLEM_H
#define CROSSOVERRESEARCH_PROBLEM_H

#include <fstream>
#include "encoding.h"

/**
 * Problem class
 * 
 * Defines attributes and characteristics of an optimization problem. Is an
 * virtual/abstract class, is a template class for concrete problems that should
 * inherit from it.
 */
class Problem {
public:
	// Type of the fitness of a chromosome
	using Fitness = typename Chrom::Fitness;

	~Problem() {}

	/**
	 * Getter to private attribute chromSize */
	uint get_chromsize();

	/**
	 * Evaluator of chromosomes.
	 * This method apply the objective function with a chromosome computing
	 * the fitness and set the resultant fitness value to the chromosome. */
	void eval(Chrom &chromosome);

	/**
	 * Apply evaluation to each chromosome in a population */
	void eval(eoPop<Chrom> &pop);

	/**
	 * Show information of the problem instance in a ostream 
	 * std::cout is the default ostream instance */
	virtual void display_info(std::ostream &os) = 0;

	/**
	 * Population initializer
	 * Initialize a population with Encoding and chromSize defined in
	 * problem instance. */
	virtual eoPop<Chrom> init_pop(uint length) = 0;

	/**
	 * Objective Function
	 * The function that defines the fitness of a chromosome, is the main 
	 * formulation of an optimization problem */
	virtual Fitness objective_function(Chrom &chromosome) = 0;

protected:
	uint __chromSize; // size of the chromosomes in this problem instance
	char *__infilename; // name of input file of this instance
	char *__name, *__acronym; // name and sigle of the problem
};

#endif //CROSSOVERRESEARCH_PROBLEM_H
