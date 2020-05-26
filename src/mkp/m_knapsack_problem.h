//
// Created by pinho on 2/16/20.
//

#ifndef CROSSOVERCOMPARATOR_M_KNAPSACK_PROBLEM_H
#define CROSSOVERCOMPARATOR_M_KNAPSACK_PROBLEM_H

#include <vector>
#include <sstream>
#include <paradiseo/eo/ga/eoBit.h>
#include <paradiseo/eo/eoInit.h>
#include <paradiseo/eo/eoPop.h>
#include <scpxx/InstanceFile.h>

#include <ga/problem.h>
#include <ga/random.h>

// namespace mkp {
//     struct item {
//         float value, weight;
//     };
// }

class MKnapsackProblem : public Problem {
public:

    using Fitness = Chrom::Fitness;

    /**
     * Default constructor 
     * @param filename nome do arquivo de instância
     */
    MKnapsackProblem(const char *);

    /*
     * Default destructor */
    ~MKnapsackProblem() = default;

    eoPop<Chrom> init_pop(uint length);

    void display_info(std::ostream &os) override;

    Fitness objective_function(Chrom& chromosome_);

protected:
    uint __numConstraints; // Número de variáveis N
    uint __numItems; // Número de restrições M
    uint __optimal; // Solução otima. Se 0, signifca que a solução ão é conhecida
    std::vector<float> __p; // Vector de valores 
    std::vector<float> __constraints; // Vector de restrições
    std::vector<std::vector<float>> __r; // Matriz de <???>

    /**
     * Verifica se uma solução quebra o conjunto de restrições da intância do
     * problema. Retorna bool.
     */
    bool break_constraint(const Chrom& chromosome_);
};

#endif //CROSSOVERCOMPARATOR_M_KNAPSACK_PROBLEM_H
