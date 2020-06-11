#ifndef CROSSOVERRESEARCH_OPTIONS_H
#define CROSSOVERRESEARCH_OPTIONS_H

#include <iostream>
#include <getopt.h>

struct cl_arguments {
    char *infile;
    uint pop_size;
    uint epochs;
    uint crossover_id;
    double crossover_rate;
    double mutation_rate;
    uint tour_size;
    char *databasefile;
    bool using_db;

    explicit cl_arguments()
    {
        this->infile = (char *) "";
        this->pop_size = 100;
        this->epochs = 50;
        this->crossover_id = 0;
        this->crossover_rate = 0.8;
        this->mutation_rate = 0.05;
        this->tour_size = 4;
        this->databasefile = (char *) "";
        this->using_db = false;
    }

    explicit cl_arguments(char* f, uint p, uint g, uint c, double cr, double mr)
    {
        this->infile = f;
        this->pop_size = p;
        this->epochs = g;
        this->crossover_id = c;
        this->crossover_rate = cr;
        this->mutation_rate = mr;
    }

    friend std::ostream& operator << (std::ostream& os, cl_arguments& cli) {
        std::string cross_name = cli.crossover_id == 0? "Uniforme" : std::to_string(cli.crossover_id).append("-Pontos");
        os << "População  : " << cli.pop_size << "\n";
        os << "N. Gerações: " << cli.epochs << "\n";
        os << "Crossover  : " << cross_name << "\n";
        os << "Tx de cruz.: " << cli.crossover_rate*100 << "%\n";
        os << "Tx de muta.: " << cli.mutation_rate*100 << "%\n";
        os << "Tam.Torneio: " << cli.tour_size << "\n";
        return os;
    }
};

option long_options[] = {
    {"infile", required_argument, 0, 'f'},
    {"db", required_argument, 0, 'd'},
    {"popsize", required_argument, 0, 'p'},
    {"epochs", required_argument, 0, 'g'},
    {"crossover", required_argument, 0, 'x'},
    {"xrate", required_argument, 0, 'c'},
    {"mrate", required_argument, 0, 'm'},
    {"ring", required_argument, 0, 'r'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

const char *short_options = "f:d:p:g:x:c:m:r:h";

const unsigned int NUM_OPTIONS = 9;

const char *DESC[NUM_OPTIONS] = {
    "Arquivo de instância do problema",
    "Arquivo .db para salvar os dados. Se não definido não salva",
    "Tamanho da população",
    "Número de épocas/gerações",
    "Operador de crossover utilizado com um ID",
    "Taxa de cruzamento (%)",
    "Taxa de mutação (%)",
    "Tamanho do Ring do operador de seleção por torneio determinístico",
    "Mostra essa lista de opções"
};

#endif // CROSSOVERRESEARCH_OPTIONS_H