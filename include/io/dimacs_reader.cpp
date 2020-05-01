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

std::vector<string> DimacsReader::read_lines(const char *filename) {
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

std::vector<std::string> DimacsReader::read_elements(const char *filename) {
	std::ifstream _infile(filename);

    if (_infile.is_open()) {
        std::string _line;
        std::stringstream _ss;
        // for each line in file, add only lines starting with "e", "n" and "p"
        while (std::getline(_infile, _line)) {
            if (_line[0] == 'p' or _line[0] == 'n' or _line[0] == 'e') {
                _ss << _line << " ";
            }
        }
        _infile.close();
        auto _fullText = _ss.str();

        auto r = split(_fullText, ' ');
        if (r.back() == "") {
            r.pop_back();
        }
        return r;
    } else {
        throw std::runtime_error("DimacsReader not opened file");
    }

}