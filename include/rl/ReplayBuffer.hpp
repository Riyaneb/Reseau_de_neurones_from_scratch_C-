#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_REPLAYBUFFER_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_REPLAYBUFFER_HPP

#include "math/Random.hpp"
#include "rl/Transition.hpp"
#include <vector>

class ReplayBuffer {
public:
    ReplayBuffer(Index size, std::uint32_t seed = 0) : size_max(size), replace_index(0), gen(seed) {}
    void add_transition(Transition const &transition);
    std::vector<Transition> get_transitions(Index size_batch);
    Index get_size() const;
    bool is_enough(Index batch_min) const;

private:
    std::vector<Transition> transitions;
    Index size_max;
    Index replace_index;
    Random gen;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_REPLAYBUFFER_HPP
