//
// Created by ronaldd on 07/04/2020.
//

#ifndef _CROSSOVER_FABRIC_H_
#define _CROSSOVER_FABRIC_H_

#include <paradiseo/eo/eoOp.h>
#include <paradiseo/eo/ga/eoBitOp.h>

#include "chromosome.h"

namespace cr {

/**
 * Crossover fabric generates instances of crossover operators (eoQuadOp)
 * Implements the Fabric Method design pattern
 */
class crossover_fabric {
public:
    /*
     * Create an instance of uniform crossover with the given bias
     * @param bias Bias for the cross mask of the crossover, default = 0.5
     */
    static eoQuadOp<chromosome> *create_uniform (double bias);

    /*
     * Create an instance of a cutpoint crossover
     * @param num is the number of cut points
     */
    static eoQuadOp<chromosome> *create_cutpoints (uint num);

    /*
     * Create an any instance of crossover operator through a ID
     * ID = 0: uniform crossover
     * ID > 0: cut points crossover with $ID points
     */
    static eoQuadOp<chromosome> *create (uint crossID);
    
};

} // end namespace cr

#endif //_CROSSOVER_FABRIC_H_
