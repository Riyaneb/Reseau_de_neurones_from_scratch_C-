#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_ACTIVATIONS_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_ACTIVATIONS_HPP

#include "ActivationLayer.hpp"
#include <cmath>

class ReLU : public ActivationLayer {
public:
    ReLU(Index nb) : ActivationLayer(nb) {}
    std::unique_ptr<Layer> clone() const override;
protected:
    Scalar apply(Scalar value) const override;
    Scalar derivate_fn(Scalar const &value) const override;
};

class Sigmoide : public ActivationLayer {
public:
    Sigmoide(Index nb) : ActivationLayer(nb) {}
    std::unique_ptr<Layer> clone() const override;
protected:
    Scalar apply(Scalar value) const override;
    Scalar derivate_fn(Scalar const &value) const override;
};

class Tanh : public ActivationLayer {
public:
    Tanh(Index nb) : ActivationLayer(nb) {}
    std::unique_ptr<Layer> clone() const override;
protected:
    Scalar apply(Scalar value) const override;
    Scalar derivate_fn(Scalar const &value) const override;
};

class Identity : public ActivationLayer {
public:
    Identity(Index nb) : ActivationLayer(nb) {}
    std::unique_ptr<Layer> clone() const override;
protected:
    Scalar apply(Scalar value) const override;
    Scalar derivate_fn(Scalar const &value) const override;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_ACTIVATIONS_HPP
