#include "math/Random.hpp"

void Random::changeSeed(std::uint32_t seed) {
    engine.seed(seed);
}

Scalar Random::randomizeUniform(int a, int b) {
    std::uniform_real_distribution<Scalar> distrib(a,b);
    return distrib(engine);
}

Scalar Random::randomizeNormal(double mean, double stddev) {
    std::normal_distribution<Scalar> distrib(mean, stddev);
    return distrib(engine);
}

Index Random::randomizeInt(int a, int b) {
    std::uniform_int_distribution<Index> distrib(a,b);
    return distrib(engine);
}
