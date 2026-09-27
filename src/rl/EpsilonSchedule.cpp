#include "rl/EpsilonSchedule.hpp"
#include <cmath>

Scalar EpsilonSchedule::linear_decay(Index count_step) const {
    if (count_step < decay_step) {
        return start_value - ( ( (Scalar)count_step/(Scalar)decay_step ) * ( start_value - end_value ));
    }
    else {
        return end_value;
    }
}

Scalar EpsilonSchedule::exponential_decay(Index count_step) const {
    if (count_step < decay_step) {
        Scalar gamma = std::pow((end_value / start_value), 1.0 / (Scalar)decay_step);
        return start_value * std::pow(gamma, (Scalar)count_step);
    }
    else {
        return end_value;
    }
}
