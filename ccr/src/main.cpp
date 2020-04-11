#include <iostream>
#include <ccr/config/configuration.h>
#include "argparser.h"

using std::cout;
using std::endl;


int main(int argc, char **argv) {
	CLI::Parse(argc, argv);

	try {
		auto conf = Configuration(CLI::ConfigFileName());

		cout << conf << endl;


	} catch (YAML::BadFile &bf) {
		std::cerr << bf.what() << std::endl;
		std::cout << "Arquivo inválido -- config.yml não encontrado." << std::endl;
		return 1;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}