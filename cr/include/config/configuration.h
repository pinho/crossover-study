//
// Created by ronaldd on 09/04/2020.
//

#ifndef CROSSOVERRESEARCH_CONFIGURATION_H
#define CROSSOVERRESEARCH_CONFIGURATION_H

#include <string>
#include <yaml-cpp/yaml.h>

/*
 * Classe Configuration
 * Deve representar uma configuração de execução do Algoritmo
 */

class Configuration {
public:
	// Default constructor
	explicit Configuration(std::string filename);
	// Default destructor
	~Configuration() = default;
	// Get the population size param from configuration file
	unsigned int popsize();
	// Get the number of generations param from configuration file
	unsigned int number_generations();
	// Get the mutations rate param from configuration file
	double mutation_rate();
	// Get the crossover rate param from configuration file
	double crossover_rate();
	// Get the name of the crossover operator
	std::string crossover_name();
	// Get the configuration ID
	std::string ID();
	// Definition of ostream operator for Configuration object
	std::ostream& operator << (std::ostream&);
private:
	YAML::Node config;
};

#endif //CROSSOVERRESEARCH_CONFIGURATION_H
