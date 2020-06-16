#ifndef _ARGPARSER_H_
#define _ARGPARSER_H_

#include <getopt.h>
#include <vector>
#include <string>

class CLI {
public:
  static void parse(int argc, char *const *argv);

private:
  static std::vector<char> s_short_options;
  static std::vector<option> s_long_options;
  static std::vector<std::string> s_descriptions;
};



void CLI::parse(int argc, char *const *argv) {

}

#endif