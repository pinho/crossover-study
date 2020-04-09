#ifndef _ARGS_HPP_
#define _ARGS_HPP_

#define PROGRAM_NAME "cr"
#define PROGRAM_EPILOG "Comparisons runner"

#include <iostream>
#include <string>
#include "args.hxx"
using namespace args;


ArgumentParser cli_parser(PROGRAM_NAME, PROGRAM_EPILOG);

// Group gp_commands(cli_parser, "Comandos", Group::Validators::Xor);
Group gp_optionals(cli_parser, "Opções");

Positional<std::string> pos_input_filename(cli_parser, "input-file", "Arquivo de entrada");

ValueFlag<uint> flag_popsize(gp_optionals, "N", "Tamanho da população usada pelo algoritmo genético\n", {'p', "popsize"});
ValueFlag<uint> flag_ngen(gp_optionals, "N", "Define o número de gerações a ser usado pelo algoritmo como critério de parada\n", {'g', "num-generations"});

HelpFlag flag_help(gp_optionals, "Help", "Mosta essa lista de opções\n", {'h', "help"});


void parse_cli(int argc, char **argv) {
    try {
        cli_parser.ParseCLI(argc, argv);
    } catch (Help) {
        std::cout << cli_parser.Help();
        exit(0);
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "Veja as opções usando a flag -h ou --help\n";
        exit(2);
    }
}

#endif