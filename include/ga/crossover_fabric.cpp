//
// Created by ronaldd on 23/04/2020.
//

#include "crossover_fabric.h"

/**
 * Cria um operador de crossover de pontos de corte a partir de um número
 * de pontos escolhido.
 * @param numPoints
 * @return um ponteiro para a nova instância de operador
 */
eoQuadOp<Chrom> * CrossoverFabric::create_cutpoints(uint numPoints) {
	if (numPoints == 1) {
		return new eo1PtBitXover<Chrom>();
	} else if (numPoints > 1) {
		return new eoNPtsBitXover<Chrom>(numPoints);
	} else {
		throw std::logic_error("CrossoverFabric: 0 cut points!");
	}
}

/**
 * Cria um operador de crossover uniforme com um dado Bias
 * @param bias
 * @return ponteiro para o novo operador
 */
eoQuadOp<Chrom> * CrossoverFabric::create_uniform(double bias) {
	return new eoUBitXover<Chrom>(bias);
}

eoQuadOp<Chrom> * CrossoverFabric::create(uint crossID) {
	if (crossID == 0) {
		return create_uniform();
	} else {
		return create_cutpoints(crossID);
	}
}
