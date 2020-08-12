//
// Created by ronaldd on 26/04/2020.
//

#ifndef CROSSOVERRESEARCH_SET_COVERING_PROBLEM_H
#define CROSSOVERRESEARCH_SET_COVERING_PROBLEM_H

#include <vector>
#include <algorithm>
#include <ga/random.h>
#include <ga/problem.h>
#include <scpxx/scp.h>

class SetCoveringProblem : public Problem {
public:
    /**
     * Construtor padrão */
    SetCoveringProblem(const char *);

    /**
     * Destrutor padrão */
    ~SetCoveringProblem() = default;

    /**
     * Retorna uma referência para o atributo matriz da instância */
    const scpxx::Matrix& get_matrix();

    /**
     * Retorna um vector contendo a quantidade de linhas que cobre cada coluna*/
    std::vector<int> coverage(const Chrom&);

    /**
     * Faz o calculo de cobertura das linhas na solução e interrompe as
     * iterações caso a uma linha não esteja sendo coberta */
    bool check_coverage(const Chrom&);

    /**
     * Verifica se todas as colunas estão sendo cobertas pela dada solução */
//    bool check_coverage(const Chrom&);

    void display_info(std::ostream& os) override;

    eoPop<Chrom> init_pop(uint length) override;

    /**
     * Função objetivo do problema de cobertura de conjuntos.
     * Conta a soma dos custos das linha selecionadas e retorna com fitness */
    Fitness objective_function(Chrom&) override;


private:
    scpxx::Matrix __matrix;
};

#endif //CROSSOVERRESEARCH_SET_COVERING_PROBLEM_H
