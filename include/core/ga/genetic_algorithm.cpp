//
// Created by ronaldd on 23/04/2020.
//

#include "genetic_algorithm.h"
//#include <iostream>

std::vector<Chrom> &GeneticAlgorithm::get_convergence() {
  return this->convergence;
}


void GeneticAlgorithm::operator()(eoPop<Chrom>& population)
{
	eoPop<Chrom> nextGen;
	Chrom _elite;
  std::cout << "Stopper: " << this->stopCriteria.className() << std::endl;

	// Clear convergence array
  if (!this->convergence.empty()) {
    this->convergence.clear();
  }

	// Main loop
	do {
		// Save current best individual
		_elite = population.best_element();
		// Select for next population
		select(population, nextGen);

		// Recombination step (crossover)
		for (size_t i=0; i < (population.size()/2); i++) {
			if (rng.flip(crossoverRate)) {
				if (cross(nextGen[2*i], nextGen[2*i+1])) {
					nextGen[2*i].invalidate(); nextGen[2*i+1].invalidate();
				}
			}
		}

		// Mutation process step
		for (size_t i=0; i < nextGen.size(); i++) {
			if (rng.flip(mutationRate)) {
				if (mutate(nextGen[i]))
					nextGen[i].invalidate();
			}
		}

		// Evaluate the new generation
		population.swap(nextGen);
    for (Chrom &individual : population) {
      problem(individual);
    }

		// Recovers the elite
		auto _worseIt = population.it_worse_element();
		*_worseIt = _elite;
    // std::cout << population.best_element().fitness() << std::endl;

		// Save to convergence
		this->convergence.push_back( population.best_element() );
	}
  while (stopCriteria(population));
	nextGen.clear();
}
