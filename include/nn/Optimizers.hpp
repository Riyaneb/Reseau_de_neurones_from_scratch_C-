#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_OPTIMIZERS_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_OPTIMIZERS_HPP
#include "Optimizer.hpp"
#include "math/Matrix.hpp"

class SGD : public Optimizer {
public :
    SGD(Scalar a = 0.1) : taux(a) {}
    void update_parameters(PairParameters &parameters) const override;

private:
    Scalar taux;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_OPTIMIZERS_HPP
