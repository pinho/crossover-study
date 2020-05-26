#include "m_knapsack_problem.h"

MKnapsackProblem::MKnapsackProblem(const char *filename) {
    using std::vector;
    
    __infilename = (char *) filename;
    __name =       (char *) "Multidimensional Knapsack Problem";
    __acronym =    (char *) "MKP";
    
    scpxx::InstanceFile<float> f(filename);

    if (f.is_open()) {
        f.bufferize();
        auto _values = f.values();
        __numItems = _values[0];
        __numConstraints = _values[1];
        __optimal = _values[2];

        __chromSize = __numItems;

        // Lendo os itens e seus valores
        __p = vector<float>(__numItems);
        for (uint i=0; i < __numItems; i++)
            __p[i] = _values[i+3];

        // Lendo valores das restrições
        __r = vector<vector<float>>(__numItems, vector<float>(__numConstraints));
        for (uint i=0; i < __numItems; i++) {
            for (uint j=0; j < __numConstraints; j++) {
                __r[i][j] = _values[ 3 + __numItems + j + i*__numItems ];
            }
        }
        int _i = 3 + __numItems + __numItems*__numConstraints;
        __constraints = vector<float>(__numConstraints);
        for (uint i=0; i < __numConstraints; i++) {
            __constraints[i] = _values[_i]; _i++;
        }
    }
}

eoPop<Chrom> MKnapsackProblem::init_pop(uint length) {
    return Random<Chrom>::population(__chromSize, length);
}

void MKnapsackProblem::display_info(std::ostream &os) {
    os << "Problem: " << __acronym << " - " << __name << "\n";
    os << "---- " << "N items: " << __numItems << "\n";
    os << "---- " << "M constraints: " << __numConstraints << "\n";
    os << "---- " << "Constraints: ";
    for (float& _f : __constraints)
        os << _f << " ";
    os << std::endl;
}

MKnapsackProblem::Fitness
MKnapsackProblem::objective_function(Chrom& chromosome_) {
    assert(chromosome_.size() == __numItems);
    // Check constraint
    // Sum r_ij * x_j
    if (break_constraint(chromosome_)) {
        return Fitness(0);
    }

    Fitness _sum = Fitness(0);
    for (uint i=0; i < __numItems; i++) {
        if (chromosome_[i])
            _sum += __p[i];
    }

    return _sum;
}


// Membro prootegido (protected)


bool MKnapsackProblem::break_constraint(const Chrom& chromosome_) {
    // somando ...
    std::vector<float> _sum(__numConstraints);
    for (uint i=0; i < __numConstraints; i++) {
        for (uint j=0; j < __numItems; j++) {
            _sum[i] += (float) (__r[i][j] * chromosome_[j]);
        }
        // checando a soma
        if (_sum[i] <= __constraints[i]) {
            continue;
        } else return true;
    }
    return false;
}
