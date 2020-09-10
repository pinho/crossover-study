#include "genetic_algorithm_scp.h"

void scp::GeneticAlgorithmSCP::operator()(eoPop<Chrom>& population,
  std::vector<Chrom>& convergence, GAInternFunctionCall callback_function)
{
  eoPop<Chrom> nextgen;
	Chrom _elite;
	int gen = 0;

	// Certifica que o vector de convergencia está limpo
	convergence.clear();

	auto start_evo = std::chrono::system_clock::now();

	// Loop principal da evolução
	do {
		gen++;
		// Salva o mlehor indivíduo atual
		_elite = population.best_element();
		// Seleção para a próxima geração
		select(population, nextgen);

		// Aplicação da operação de cruzamento / crossover
		for (size_t i=0; i < (population.size()/2); i++) {
			if (rng.flip(crossoverRate)) {
				if (cross(nextgen[2*i], nextgen[2*i+1])) {
					nextgen[2*i].invalidate(); nextgen[2*i+1].invalidate();
				}
			}
		}

		// Aplicação do operador de mutação
		for (size_t i=0; i < nextgen.size(); i++) {
			if (rng.flip(mutationRate)) {
				if (mutate(nextgen[i]))
					nextgen[i].invalidate();
			}
		}

    // Aplica o operador de factibilidade nos cromossomos recém-gerados
    for (size_t i=0; i < nextgen.size(); i++) {
      scp_instance.make_feasible(nextgen[i]);
    }
		// Aplica avaliação a nova geração
		scp_instance.eval(nextgen);
		population.swap(nextgen);

		// Recupera o elite
		auto _worseIt = population.it_worse_element();
		*_worseIt = _elite;

		convergence.push_back( population.best_element() );
		callback_function(gen, population);

	} while (stopCriteria(population));

	this->evolution_time = system_clock::now() - start_evo;
	nextgen.clear();
}