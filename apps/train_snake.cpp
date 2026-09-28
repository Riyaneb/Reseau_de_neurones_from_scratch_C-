#include <iostream>
#include <thread>

#include "env/SnakeEnv.hpp"
#include "io/Serializer.hpp"
#include "rl/DQNAgent.hpp"
#include "utils/Logger.hpp"

int main() {
    SnakeEnv snake(10,100);
    ConfigurationAgent config;
    print_configuration(config);
    delay(3000);
    DQNAgent agent(snake.get_observation_size(),snake.get_action_count(),config);
    const Index EPOCH = 5000;
    for (Index i = 0; i < EPOCH; i++) {
        Matrix actual_observation = snake.reset();
        bool end = false;
        while (!end) {
            Scalar actual_action = agent.choice_action(actual_observation);
            StepResult result_action = snake.step(actual_action);
            Transition transition(actual_observation, actual_action, result_action.reward, result_action.observation, result_action.end_step);
            agent.add_buffer(transition);
            agent.learn();
            actual_observation = result_action.observation;
            end = result_action.end_step;
        }
        if (i%50==0) {
            std::cout << "Epoch " << i << " : Perte actuel : " << agent.get_loss() << " ; Score à cette epoch : " << snake.get_score() << " ; Nombre d'étape réalisée : " << agent.get_step_count() << " ; Valeur epilon actuel : " << agent.actual_epsilon() << " ; Taille du buffer actuel : " << agent.get_size_buffer() << std::endl;
        }
    }

    bool end = false;
    Matrix finale_observation = snake.reset();
    std::cout << "Souhaitez-vous voir le resultat après entrainement ? (y/n) : ";
    char c;
    std::cin >> c;
    if (c == 'y') {
        while (!end) {
            snake.render();
            clear();
            delay(200);
            Index action = agent.choice_action(finale_observation);
            StepResult final_result = snake.step(action);
            finale_observation = final_result.observation;
            end = final_result.end_step;
        }
    }
    snake.render();
    Network net_clone = agent.get_network();
    save(net_clone,"models/reseau_agent_snake.txt");
}