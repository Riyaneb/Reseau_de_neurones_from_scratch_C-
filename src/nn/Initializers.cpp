#include "nn/Initializers.hpp"

void init_weight_Glorot(Matrix &weight, Random &gen) {
    Index fan_in = weight.get_row();
    Index fan_out = weight.get_column();
    double stdev = std::sqrt(2.0/(fan_in + fan_out));

    for (Index i = 0; i < fan_in; i++) {
        for (Index j = 0; j < fan_out; j++) {
            weight.get_value(i,j) = gen.randomizeNormal(0, stdev);
        }
    }
}

void init_weight_He(Matrix &weight, Random &gen) {
    Index fan_in = weight.get_row();
    Index fan_out = weight.get_column();
    double stdev = std::sqrt(2.0/fan_in);
    for (Index i = 0; i < fan_in; i++) {
        for (Index j = 0; j < fan_out; j++) {
            weight.get_value(i,j) = gen.randomizeNormal(0, stdev);
        }
    }
}
