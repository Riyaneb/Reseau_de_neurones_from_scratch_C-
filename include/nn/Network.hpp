#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_NETWORK_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_NETWORK_HPP

#include "nn/Layer.hpp"
#include <memory>
#include <vector>
#include <cassert>
#include <utility>

class Network {
public:
    void add(std::unique_ptr<Layer>);
    Matrix prediction(Matrix const &X);
private:
    std::vector<std::unique_ptr<Layer>> layers;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_NETWORK_HPP
