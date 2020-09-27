#ifndef CROSSOVERRESEARCH_PARSE_H
#define CROSSOVERRESEARCH_PARSE_H 1

#include "options.h"
#include <cstdio>

/**
 * Mostra o menu de ajuda das opções de linha de comandos
 */
void show_help(char **argv);

/**
 * Anaçisar os argumentos passados por linha de comando
 */
CLI *parse(int argc, char **argv);

/**
 * Define uma string ID para cada cominação de parâmetros
 */
std::string identify(CLI& cli);

#endif//CROSSOVERRESEARCH_PARSE_H