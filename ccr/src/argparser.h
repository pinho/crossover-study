#ifndef CCR_ARG_PARSER_H
#define CCR_ARG_PARSER_H

#include <iostream>
#include "args.hxx"
#include "settings.h"

namespace CLI {

    // Definção das opções de linha de comandos
    args::ArgumentParser parser(PROGRAM_RUNNER);
    args::ValueFlag<std::string> config(parser, "file",
            "Arquivo de configuração de execução", {'c', "config"});

    // Parse options passed in command-line options
    void Parse(int argc, char **argv) {
        try {
            parser.ParseCLI(argc, argv);
        } catch (args::Help&) {
            std::cout << parser.Help();
            exit(0);
        } catch (args::Error &e) {
            std::cerr << e.what() << std::endl;
            exit(2);
        }
    }

    // Returns the string getted from command-line option for configuration
    // file, or the default value for it
    std::string ConfigFileName() {
        return bool(config) ? args::get(config) : "config.yml";
    }

    

}

#endif