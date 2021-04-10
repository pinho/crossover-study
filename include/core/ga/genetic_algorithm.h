//
// Created by ronaldd on 23/04/2020.
//

#ifndef CROSSOVERRESEARCH_GENETIC_ALGORITHM_H
#define CROSSOVERRESEARCH_GENETIC_ALGORITHM_H

#include <paradiseo/eo/eoSGA.h>
#include "problem.h"

class GeneticAlgorithm {
public:
	typedef typename Chrom::Fitness Fitness;
	//typedef void (*GAInternFunctionCall)(int, eoPop<Chrom>&);

	// Default constructor
	explicit GeneticAlgorithm(
			eoEvalFunc<Chrom>& problem_,
			eoSelectOne<Chrom> &selectOp_,
			eoQuadOp<Chrom> &crossoverOp_,
			const float crossoverRate_,
			eoMonOp<Chrom> &mutationOp_,
			const float mutationRate_,
			eoContinue<Chrom> &continue_
	) : problem(problem_),
		select(selectOp_),
		cross(crossoverOp_),
		mutate(mutationOp_),
		stopCriteria(continue_),
		crossoverRate(crossoverRate_),
		mutationRate(mutationRate_)
	{}

	// Default destructor
	~GeneticAlgorithm() = default;

  // Getter for the convergence vector
  std::vector<Chrom> &get_convergence();

	// Main operator of the GA
	// Gets a reference to a population object and evolve it
	// Gets also a function to manipulate the population and is called
	// at end of each generation
	virtual void operator()(eoPop<Chrom>& population);

protected:
	eoEvalFunc<Chrom>& problem;
	eoSelectPerc<Chrom> select;
	eoInvalidateQuadOp<Chrom> cross;
	eoInvalidateMonOp<Chrom> mutate;
	eoContinue<Chrom>& stopCriteria;
	float crossoverRate;
	float mutationRate;
  std::vector<Chrom> convergence;
};

#endif //CROSSOVERRESEARCH_GENETIC_ALGORITHM_H
