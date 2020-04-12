#include <iostream>
#include <ccr/config/configuration.h>
#include "argparser.h"

using std::cout;
using std::endl;


int main(int argc, char **argv) {
	cli::parse(argc, argv);

	std::cout << "Arquivo de configuração: " << cli::configfilename << std::endl;

	return 0;
}