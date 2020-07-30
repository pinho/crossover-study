//
// Created by ronaldd on 26/04/2020.
//

#include "split.h"

std::vector<std::string> split(const std::string &txt, const char separator) {
  std::vector<std::string> result;
	uint begin = 0;
	for (uint64_t i=0; i < txt.size(); i++) {
		if (txt[i] == separator) {
			if (i > begin)
				result.push_back( txt.substr(begin, i-begin) );
			begin = i+1;
		}
	}
	result.push_back( txt.substr(begin, txt.size()) );
	return result;
}