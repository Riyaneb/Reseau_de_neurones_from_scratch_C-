#include <iostream>
#include <thread>

#include "env/SnakeEnv.hpp"
#include "io/Serializer.hpp"
#include "rl/DQNAgent.hpp"
#include "utils/Logger.hpp"


int main() {
    SnakeEnv snake(10,1000,33);
    ConfigurationAgent config;
    print_configuration(config);
    delay(5000);
    DQNAgent agent(snake.get_observation_size(),snake.get_action_count(), config);
    agent.load_network("models/reseau_agent_snake.txt");
    bool end = false;
    Matrix finale_observation = snake.reset();
    while (!end) {
        snake.render();
        clear();
        delay(200);
        Index action = agent.choice_action_test(finale_observation);
        StepResult final_result = snake.step(action);
        finale_observation = final_result.observation;
        end = final_result.end_step;
    }
    snake.render();
}