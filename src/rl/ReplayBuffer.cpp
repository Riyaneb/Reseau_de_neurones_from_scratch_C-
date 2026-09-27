#include "rl/ReplayBuffer.hpp"
#include <cassert>

void ReplayBuffer::add_transition(Transition const &transition) {
    if ((int)transitions.size() < size_max) {
        transitions.push_back(transition);
    }
    else {
        transitions[replace_index] = transition;
        replace_index = (replace_index + 1) % size_max;
    }
}

std::vector<Transition> ReplayBuffer::get_transitions(Index size_batch) {
    assert(size_batch <= (int)transitions.size() && "Erreur : La taille du batch demandé dépasse le nombre de transistion disponible");
    std::vector<Transition> result;
    for (Index i = 0; i < size_batch; ++i) {
        result.push_back(transitions[gen.randomizeInt(0, (int)transitions.size() - 1)]);
    }
    return result;
}

Index ReplayBuffer::get_size() const {
    return transitions.size();
}

bool ReplayBuffer::is_enough(Index batch_min) const {
    return (int)transitions.size() >= batch_min;
}
