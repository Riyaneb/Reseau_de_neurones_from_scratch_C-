#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_CORRIDORENV_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_CORRIDORENV_HPP
#include "env/Environment.hpp"
#include <cassert>

class CorridorEnv : public Environment {
public:
    CorridorEnv(Index size_cor, Index limit) : position(0), step_count(0), corridor_size(size_cor), step_limit(limit) {
        assert(size_cor >= 2 && "Erreur : La taille du couloir doit au moins valoir 2");
    }
    Matrix reset() override;
    StepResult step(Index action) override;
    Index get_observation_size() const override;
    Index get_action_count() const override;
    void render() const override;
    void set_seed(Index) override {}
private:
    Index position;
    Index step_count;
    Index corridor_size;
    Index step_limit;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_CORRIDORENV_HPP
