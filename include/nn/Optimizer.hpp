#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_OPTIMIZER_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_OPTIMIZER_HPP
#include "math/Types.hpp"

class Optimizer {
public :
    virtual ~Optimizer() {}
    virtual void update_parameters(PairParameters &parameters) const = 0;
};


#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_OPTIMIZER_HPP
