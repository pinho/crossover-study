#ifndef CROSSOVERRESEARCH_OPTIONS_H
#define CROSSOVERRESEARCH_OPTIONS_H

#include <iostream>
#include <ostream>
#include <getopt.h>
#include <string>

struct CLI {
    char *infile;
    unsigned int pop_size;
    unsigned int stop_criteria;
    unsigned int crossover_id;
    double crossover_rate;
    double mutation_rate;
    unsigned int tour_size;
    char *databasefile;
    bool using_db;
    bool verbose;

    explicit CLI()
    {
        this->infile = (char *) "";
        this->pop_size = 100;
        this->stop_criteria = 50;
        this->crossover_id = 0;
        this->crossover_rate = 0.8;
        this->mutation_rate = 0.05;
        this->tour_size = 8;
        this->databasefile = (char *) "";
        this->using_db = false;
        this->verbose = false;
    }

    explicit CLI(char* f, unsigned int p, unsigned int g, unsigned int c, double cr, double mr)
    {
        this->infile = f;
        this->pop_size = p;
        this->stop_criteria = g;
        this->crossover_id = c;
        this->crossover_rate = cr;
        this->mutation_rate = mr;
    }

    friend std::ostream& operator << (std::ostream& os, CLI& cli) {
        std::string cross_name = cli.crossover_id == 0? "Uniforme" : std::to_string(cli.crossover_id).append("-Pontos");
        os << "População  : " << cli.pop_size << "\n";
        os << "N. Gerações: " << cli.stop_criteria << "\n";
        os << "Crossover  : " << cross_name << "\n";
        os << "Tx de cruz.: " << cli.crossover_rate*100 << "%\n";
        os << "Tx de muta.: " << cli.mutation_rate*100 << "%\n";
        os << "Tam.Torneio: " << cli.tour_size << "\n";
        return os;
    }
};

#endif // CROSSOVERRESEARCH_OPTIONS_H
