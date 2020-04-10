#include <iostream>
#include <config/configuration.h>

int main() {
	try {
		auto conf = Configuration("test.yaml");
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}