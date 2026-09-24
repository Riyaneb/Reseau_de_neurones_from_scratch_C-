#include "nn/Activations.hpp"
#include <cassert>

Scalar ReLU::apply(Scalar value) const {
    if (value < 0) {
        return 0;
    }
    else {
        return value;
    }
}

Scalar ReLU::derivate_fn(Scalar const &value) const {
    if (value <= 0) {
        return 0;
    }
    else {
        return 1;
    }
}

Scalar Sigmoide::apply(Scalar value) const {
    return 1.0/(1.0 + std::exp(-value));
}

Scalar Sigmoide::derivate_fn(Scalar const &value) const {
    Scalar temp = Sigmoide::apply(value);
    return temp * (1.0 - temp);
}

Scalar Tanh::apply(Scalar value) const {
    return std::tanh(value);
}

Scalar Tanh::derivate_fn(Scalar const &value) const {
    return 1.0 - pow(std::tanh(value),2);
}

Scalar Identity::apply(Scalar value) const {
    return value;
}

Scalar Identity::derivate_fn(Scalar const &value) const {
    if (value <= 0) {
    }
    return 1;
}