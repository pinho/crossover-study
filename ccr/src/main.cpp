#include <iostream>
#include "argparser.h"

#include <ccr/ga/crossover_fabric.h>

using std::cout;
using std::endl;


int main(int argc, char **argv) {
	cli::parse(argc, argv);

	std::cout << "Arquivo de configuração: " << cli::configfilename << std::endl;

	eoQuadOp<Chrom>* x1_ptr = CrossoverFabric::create_uniform();
	auto x2_ptr = CrossoverFabric::create_cutpoints(2);
	auto x3_ptr = CrossoverFabric::create(0);

	std::cout << x1_ptr->className() << std::endl;
	std::cout << x2_ptr->className() << std::endl;
	std::cout << x3_ptr->className() << std::endl;

	return 0;
}