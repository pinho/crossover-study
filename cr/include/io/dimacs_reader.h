//
// Created by ronaldd on 09/04/2020.
//

#ifndef CROSSOVERRESEARCH_DIMACS_READER_H
#define CROSSOVERRESEARCH_DIMACS_READER_H

#include <string>
#include <sstream>
#include <vector>

namespace cr {

class DimacsReader {
public:
	static std::vector<std::string> read(std::string filename);
};

}

#endif //CROSSOVERRESEARCH_DIMACS_READER_H
