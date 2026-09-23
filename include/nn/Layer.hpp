#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_LAYER_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_LAYER_HPP

#include "math/Matrix.hpp"

class Layer {
public:
    virtual Matrix forward(Matrix const &in) = 0;
    virtual ~Layer();
    virtual Index nInput() const = 0;
    virtual Index nOutput() const = 0;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_LAYER_HPP
