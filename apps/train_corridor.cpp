#include <iostream>
#include <ostream>

#include "env/CorridorEnv.hpp"
#include "rl/DQNAgent.hpp"

int main() {
    CorridorEnv corridor(5,50);
    DQNAgent agent(corridor.get_observation_size(),corridor.get_action_count());
    const Index EPOCH = 500;
    for (Index i = 0; i < EPOCH; i++) {
        Scalar total_reward = 0;
        Matrix actual_observation = corridor.reset();
        bool end = false;
        while (!end) {
            Scalar actual_action = agent.choice_action(actual_observation);
            StepResult result_action = corridor.step(actual_action);
            Transition transition(actual_observation, actual_action, result_action.reward, result_action.observation, result_action.end_step);
            agent.add_buffer(transition);
            agent.learn();
            actual_observation = result_action.observation;
            end = result_action.end_step;
            total_reward += result_action.reward;
        }
        if (i%50==0) {
            std::cout << "Epoch " << i << " : Perte actuel : " << agent.get_loss() << " ; Récompense total : " << total_reward << " ; Nombre d'étape réalisée : " << agent.get_step_count() << " ; Valeur epilon actuel : " << agent.actual_epsilon() << " ; Taille du buffer actuel : " << agent.get_size_buffer() << std::endl;
        }
    }

    bool end = false;
    Matrix finale_observation = corridor.reset();
    while (!end) {
        corridor.render();
        Index action = agent.choice_action(finale_observation);
        StepResult final_result = corridor.step(action);
        finale_observation = final_result.observation;
        end = final_result.end_step;
    }
    corridor.render();

}