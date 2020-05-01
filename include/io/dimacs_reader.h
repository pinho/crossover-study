//
// Created by ronaldd on 09/04/2020.
//

#ifndef CROSSOVERRESEARCH_DIMACS_READER_H
#define CROSSOVERRESEARCH_DIMACS_READER_H

#include <string>
#include <sstream>
#include <vector>

#include "utils.h"

class DimacsReader {
public:
	/**
	 * Read dimacs file per lines
	 * Returns a vector of strings where each elements is a line */
	static std::vector<std::string> read_lines(const char *filename);

	/**
	 * Read a dimacs format file catching all elements (words and symbols)
	 * separated by space.
	 * Returns a vector of string where each string is a element on file */
	static std::vector<std::string> read_elements(const char *filename);
};

#endif //CROSSOVERRESEARCH_DIMACS_READER_H
