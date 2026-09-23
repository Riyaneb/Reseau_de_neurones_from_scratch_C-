#include "nn/ActivationLayer.hpp"
#include <cassert>

Index ActivationLayer::nInput() const {
    return nbInput;
}

Index ActivationLayer::nOutput() const {
    return nbInput;
}

Matrix ActivationLayer::forward(Matrix const &in) {
    assert(in.get_column() == nbInput && "Erreur : Dimension dans le forward activationLayer Incorrecte");
    input = in;
    Matrix result(input.get_row(), input.get_column());
    for (Index i = 0; i < input.get_row(); i++) {
        for (Index j = 0; j < input.get_column(); j++) {
            result.get_value(i,j) = apply(input.get_value(i,j));
        }
    }
    return result;
}