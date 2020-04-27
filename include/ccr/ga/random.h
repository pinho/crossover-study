#ifndef CROSSOVERRESEARCH_RANDOM_H
#define CROSSOVERRESEARCH_RANDOM_H


template <class Encoding> class Random {
public:
    static Encoding uniform_chromosome(uint);
};

#endif//CROSSOVERRESEARCH_RANDOM_H