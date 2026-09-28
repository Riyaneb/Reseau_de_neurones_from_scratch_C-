#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_EPSILONSCHEDULE_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_EPSILONSCHEDULE_HPP
#include "math/Types.hpp"
#include <cassert>

class EpsilonSchedule {
public:
    EpsilonSchedule(Scalar start = 1.0, Scalar end = 0.02, Index step = 80000) : start_value(start), end_value(end), decay_step(step) {
        assert((start <= 1.0 && start >= end) && (end > 0.0 && end <= start) && step > 0 && "Erreur : Donnée EpsilonSchedule invalide");
    }
    Scalar linear_decay(Index count_step) const;
    Scalar exponential_decay(Index count_step) const;
private:
    Scalar start_value;
    Scalar end_value;
    Index decay_step;

};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_EPSILONSCHEDULE_HPP
