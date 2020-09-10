#ifndef _SET_COVERING_GENETIC_ALG_H
#define _SET_COVERING_GENETIC_ALG_H

#include <chrono>
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::nanoseconds;
using std::chrono::system_clock;

#include <core/ga/genetic_algorithm.h>
#include <core/ga/problem.h>
#include "set_covering_problem.h"

namespace scp {

  class GeneticAlgorithmSCP {
  public:
    typedef typename Chrom::Fitness Fitness;
    typedef void (*GAInternFunctionCall)(int, eoPop<Chrom>&);

    // Default constructor
    explicit GeneticAlgorithmSCP(
        SetCoveringProblem &problem_,
        eoSelectOne<Chrom> &selectOp_,
        eoQuadOp<Chrom> &crossoverOp_,
        const float crossoverRate_,
        eoMonOp<Chrom> &mutationOp_,
        const float mutationRate_,
        eoContinue<Chrom> &continue_
    ) : scp_instance(problem_),
      select(selectOp_),
      cross(crossoverOp_),
      mutate(mutationOp_),
      stopCriteria(continue_),
      crossoverRate(crossoverRate_),
      mutationRate(mutationRate_)
    {}

    // Default destructor
    ~GeneticAlgorithmSCP() = default;

    // Main operator of the GA
    // Gets a reference to a population object and evolve it
    // Gets also a function to manipulate the population and is called
    // at end of each generation
    virtual void operator()(eoPop<Chrom>& population, std::vector<Chrom>& conv,
        GAInternFunctionCall callback);

    nanoseconds& duration_of_last_execution() {
      return this->evolution_time;
    }

  protected:
    SetCoveringProblem& scp_instance;
    eoSelectPerc<Chrom> select;
    eoInvalidateQuadOp<Chrom> cross;
    eoInvalidateMonOp<Chrom> mutate;
    eoContinue<Chrom>& stopCriteria;
    float crossoverRate;
    float mutationRate;
    nanoseconds evolution_time;
  };

}

#endif