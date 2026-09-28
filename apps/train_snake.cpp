#include <iostream>
#include <thread>

#include "env/SnakeEnv.hpp"
#include "io/Serializer.hpp"
#include "rl/DQNAgent.hpp"
#include "utils/Logger.hpp"
#include <fstream>
#include <deque>

void update_log(std::ofstream &log_file, std::deque<Scalar> &recent_scores, Scalar &sum_scores, Index episode, Scalar score, Scalar epsilon, Scalar loss) {
    recent_scores.push_front(score);
    sum_scores += score;

    if (recent_scores.size() > 100) {
        sum_scores -= recent_scores.back();
        recent_scores.pop_back();
    }

    Scalar rolling_mean = sum_scores / recent_scores.size();

    if (log_file) {
        log_file << episode << ","<< score << ","<< epsilon << ","<< loss << ","<< rolling_mean << "\n";
    }
}

int main() {
    SnakeEnv snake(10,100);

    Random gen(33);
    ConfigurationAgent config;
    print_configuration(config);

    delay(3000);

    DQNAgent agent(snake.get_observation_size(),snake.get_action_count(),config);
    agent.load_network("models/reseau_agent_snake.txt");

    std::ofstream log_file("data/training_snake_log.csv");
    if (log_file) {
        log_file << "episode,score,epsilon,loss,mean_score\n";
    }
    std::deque<Scalar> recent_scores;
    Scalar sum_scores = 0.0;

    Scalar best_mean = -1;
    const Index EPOCH = 3000;

    for (Index i = 0; i < EPOCH; i++) {
        if (i%100==0 && i>0) {
            SnakeEnv env2(10,100,gen.randomizeInt(0,4444));
            Scalar mean_score = eval_snake(agent,env2,20);
            std::cout << "\nEvaluation score moyen à l'epoch " << i << " : " << mean_score << std::endl;
            if (mean_score > best_mean) {
                std::cout << "Nouveau meilleur score moyen, sauvegarde du nouveau meilleur modèle !" << std::endl;
                best_mean = mean_score;
                Network net_clone = agent.get_network();
                save(net_clone,"models/reseau_agent_snake.txt");
            }
        }
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
        Scalar current_score = snake.get_score();
        if (i%50==0) {
            std::cout << "\nEpoch " << i << " : Perte actuel : " << agent.get_loss() << " ; Score à cette epoch : " << current_score << " ; Nombre d'étape réalisée : " << agent.get_step_count() << " ; Valeur epilon actuel : " << agent.actual_epsilon() << " ; Taille du buffer actuel : " << agent.get_size_buffer() << std::endl;
        }
        update_log(log_file, recent_scores, sum_scores, i, current_score, agent.actual_epsilon(), agent.get_loss());
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

    SnakeEnv env2(10,100,gen.randomizeInt(0,7777));
    Scalar mean_score = eval_snake(agent,env2,200);
    std::cout << "Evaluation score moyen final : " << mean_score << std::endl;

}