#include "env/CorridorEnv.hpp"

#include <iostream>

Matrix CorridorEnv::reset() {
    position = 0;
    step_count = 0;
    Scalar observation = static_cast<Scalar>(position) /(corridor_size - 1);
    Matrix temp(1,1,observation);
    return temp;
}

Index CorridorEnv::get_action_count() const {
    return 2;
}

Index CorridorEnv::get_observation_size() const {
    return 1;
}

void CorridorEnv::render() const {
    for (int i = 0; i < corridor_size; i++) {
        if (i == position) {
            std::cout << "@";
        }
        else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

StepResult CorridorEnv::step(Index action) {
    assert((action == 0 || action == 1) && "Erreur : L'action choisis n'est pas définie");
    Scalar reward = 0;
    bool end = false;
    step_count++;
    switch (action) {
        case 0:
            if (position != 0) {
                position--;
            }
            break;
        case 1:
            position++;
            if (position >= corridor_size-1) {
                reward = 1;
                end = true;
            }
            break;
    }
    if (step_count >= step_limit) {
        end = true;
    }
    Scalar observation = static_cast<Scalar>(position) / (corridor_size - 1);
    return StepResult(Matrix(1,1,observation),reward,end);
}




