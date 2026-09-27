#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_ENVIRONMENT_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_ENVIRONMENT_HPP
#include "math/Matrix.hpp"

struct StepResult {
    Matrix observation;
    Scalar reward;
    bool end_step;
    StepResult(Matrix const &o, Scalar r, bool end) : observation(o), reward(r), end_step(end) {}
};


class Environment {
    public:
    virtual ~Environment() {}
    virtual Matrix reset() = 0;
    virtual StepResult step(Index action) = 0;
    virtual Index get_observation_size() const = 0;
    virtual Index get_action_count() const = 0;
    virtual void render() const = 0;
    virtual void set_seed(Index) {}
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_ENVIRONMENT_HPP
