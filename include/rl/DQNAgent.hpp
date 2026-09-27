#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_DQNAGENT_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_DQNAGENT_HPP

#include "nn/Network.hpp"
#include "nn/Optimizers.hpp"
#include "rl/ReplayBuffer.hpp"
#include "rl/Transition.hpp"
#include "rl/EpsilonSchedule.hpp"
#include "env/Environment.hpp"
#include "nn/Losses.hpp"
#include "nn/DenseLayer.hpp"
#include "nn/Activations.hpp"

class DQNAgent {
public:
    DQNAgent(Index size_observation, Index am_action, std::uint32_t seed = 0, Index amount_neural = 64, Scalar value_gamma = 0.95, Index value_size_batch = 32, Index value_min_amount_transition = 500, Index value_update_intervale = 200, Index buffer_size = 10000, Scalar learning_rate = 0.001);
    Index choice_action(Matrix const &observation);
    void add_buffer(Transition const &transition);
    void sync_target();
    void learn();

    Scalar get_loss();
    Scalar actual_epsilon();
    Index get_size_buffer();
    Index get_step_count();
private:
    Random gen;
    Index amount_observation;
    Index amount_action;
    Network main_network;
    Network target_network;
    PairParameters parameters;
    std::unique_ptr<Optimizer> optimizer;
    QuadraLoss loss_fn;
    ReplayBuffer replay_buffer;
    EpsilonSchedule epsilon_schedule;
    Index step_count;
    Scalar gamma;
    Index size_batch;
    Index min_amount_transition;
    Index target_update_interval;
    Scalar loss_value;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_DQNAGENT_HPP
