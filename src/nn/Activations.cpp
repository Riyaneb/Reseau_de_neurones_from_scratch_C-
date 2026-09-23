#include "nn/Activations.hpp"

Scalar ReLU::apply(Scalar value) const {
    if (value < 0) {
        return 0;
    }
    else {
        return value;
    }
}

Scalar Sigmoide::apply(Scalar value) const {
    return 1.0/(1.0 + std::exp(-value));
}

Scalar Tanh::apply(Scalar value) const {
    return std::tanh(value);
}

Scalar Identity::apply(Scalar value) const {
    return value;
}