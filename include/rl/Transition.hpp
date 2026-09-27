#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_TRANSITION_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_TRANSITION_HPP

#include "math/Matrix.hpp"

struct Transition {
    Matrix start_state;
    Index action;
    Scalar reward;
    Matrix end_state;
    bool end_game;
    Transition(Matrix start_s, Index act, Scalar r, Matrix end_s, bool end_g) : start_state(start_s), action(act), reward(r), end_state(end_s), end_game(end_g) {}
};


#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_TRANSITION_HPP
