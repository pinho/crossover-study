//
// Created by ronaldd on 23/04/2020.
//

#include "genetic_algorithm.h"

void GeneticAlgorithm::operator()(eoPop<Chrom>& population,
		void callback(int, eoPop<Chrom>&) = [](int g, eoPop<Chrom>& p) {})
{
	eoPop<Chrom> _nextGen;
	Chrom _elite;
	int gen = 0;

	// Main loop
	do {
		gen++;
		// Save current best individual
		_elite = population.best_element();
		// Select for next population
		select(population, _nextGen);
		// Recombination step (crossover)
		for (size_t i=0; i < (population.size()/2); i++) {
			if (rng.flip(crossoverRate)) {
				if (cross(_nextGen[2*i], _nextGen[2*i+1])) {
					_nextGen[2*i].invalidate(); _nextGen[2*i+1].invalidate();
				}
			}
		}
		// Mutation process step
		for (size_t i=0; i < _nextGen.size(); i++) {
			if (rng.flip(mutationRate)) {
				if (mutate(_nextGen[i]))
					_nextGen[i].invalidate();
			}
		}
		// Evaluate the new generation
		population.swap(_nextGen);
		problem.eval(population);

		// Recovers the elite
		auto _worseIt = population.it_worse_element();
		*_worseIt = _elite;

		// call the custom function
		callback(gen, population);
		
	} while (stopCriteria(population));
	_nextGen.clear();
}