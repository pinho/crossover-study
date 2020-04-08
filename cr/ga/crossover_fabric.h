//
// Created by ronaldd on 07/04/2020.
//

#ifndef _CROSSOVER_FABRIC_H_
#define _CROSSOVER_FABRIC_H_

#include <paradiseo/eo/eoOp.h>

#include "chromosome.h"

namespace cr {

/**
 * Crossover fabric generates instances of crossover operators (eoQuadOp)
 * Implements the Fabric Method design pattern
 */
class crossover_fabric {
public:

    static eoQuadOp<chromosome> *create_uniform (double);

    static eoQuadOp<chromosome> *create_cutpoints (uint);

    static eoQuadOp<chromosome> *create (uint);
    
};

} // end namespace cr

#endif //_CROSSOVER_FABRIC_H_
