#ifndef CCR_ARG_PARSER_H
#define CCR_ARG_PARSER_H

#include <getopt.h>
#include <iostream>
#include <string>

namespace cli {

  const char *SHORT_OPTIONS = "c:h";

  const option LONG_OPTIONS[] = {
    {"config", required_argument, nullptr, 'c'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, no_argument, nullptr, 0}
  };

  std::string configfilename = "config.yml";


  void print_help() {
      std::cout << "Options:\n\n";
      for (int i = 0; i < 2; i++) {
          std::cout << " -" << char(LONG_OPTIONS[i].val) << ", --" << LONG_OPTIONS[i].name << "\n";
      }
  }


  void parse(int argc, char **argv) {
    int opt;
    while ((opt = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, 0)) != EOF) {
        switch (opt) {
            case 'c':
                if (optarg) configfilename = std::string(optarg);
                break;
            case 'h':
            default:
                print_help();
                break;
        }
    }
  }


}

#endif