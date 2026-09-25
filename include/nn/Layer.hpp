#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_LAYER_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_LAYER_HPP

#include "math/Matrix.hpp"

class Layer {
public:
    virtual Matrix forward(Matrix const &in) = 0;
    virtual Matrix backward(Matrix const &gradientOut) = 0;
    virtual ~Layer() = default;
    virtual Index nInput() const = 0;
    virtual Index nOutput() const = 0;
    virtual PairParameters get_parameters();
    virtual void set_gradients_zero();
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_LAYER_HPP
