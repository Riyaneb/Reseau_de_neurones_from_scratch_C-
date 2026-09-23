#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_DENSELAYER_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_DENSELAYER_HPP

#include "math/Matrix.hpp"
#include "math/Random.hpp"
#include "nn/Initializers.hpp"
#include "nn/Layer.hpp"

class DenseLayer : public Layer {
public:
    DenseLayer(Index nInput,Index nOutput, Random &gen, Index initChoice=0);
    Matrix forward(Matrix const &in) override;
    Index nInput() const override;
    Index nOutput() const override;

    void set_weight(Matrix const &w);
    void set_biais(Matrix const &b);
    const Matrix& get_weight() const;
    const Matrix& get_biais() const;
private:
    Matrix weight;
    Matrix biais;
    Matrix inNeural;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_DENSELAYER_HPP
