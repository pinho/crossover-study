//
// Created by ronaldd on 09/04/2020.
//

#include "dimacs_reader.h"
#include <fstream>
using std::vector;
using std::string;

auto append = [](vector<string>& v, string& l) {
	if (l.front() != 'c')
		v.emplace_back(l);
};

std::vector<string> DimacsReader::read(std::string filename) {
	vector<string> _vec;
	string _line;
	try {
		std::ifstream _infile(filename);
		if (_infile.is_open()) {
			while (getline(_infile, _line)) {
				append(_vec, _line);
			}
		}
		_infile.close();
		return _vec;
	} catch (std::exception &e) {
		std::string _msg = "DimacsReader can't read the file";
		_msg.append(filename);
		throw std::runtime_error(_msg);
	}

}