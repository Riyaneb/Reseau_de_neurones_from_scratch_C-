#include "nn/Losses.hpp"

Scalar QuadraLoss::calculate_loss(Matrix const &prediction, Matrix const &target) const {
    assert(prediction.get_row() == target.get_row() && prediction.get_column() == target.get_column() && "Erreur : Les matrices n'ont pas la même dimension");
    Scalar loss_value = 0.0;
    for (Index i = 0; i < prediction.get_row(); i++) {
        for (Index j = 0; j < prediction.get_column(); j++) {
            loss_value += std::pow(target.get_value(i,j) - prediction.get_value(i,j),2);
        }
    }
    loss_value = loss_value / (2.00 * prediction.get_row());
    return loss_value;
}

Matrix QuadraLoss::calculate_gradients_loss(Matrix const &prediction, Matrix const &target) const {
    assert(prediction.get_row() == target.get_row() && prediction.get_column() == target.get_column() && "Erreur : Les matrices n'ont pas la même dimension");
    Matrix grad = prediction - target;
    Scalar n = prediction.get_row();
    for (Index i = 0; i < grad.get_row(); i++) {
        for (Index j = 0; j < grad.get_column(); j++) {
            grad.get_value(i,j) = grad.get_value(i,j) / n;
        }
    }
    return grad;
}


