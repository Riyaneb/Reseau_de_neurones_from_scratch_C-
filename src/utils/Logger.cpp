#include <iostream>
#include <thread>

#include "rl/DQNAgent.hpp"
#include <sstream>
#include "math/Matrix.hpp"

void print_configuration(ConfigurationAgent const &config) {
    std::cout << "Configuration Agent :\n";
    std::cout << "seed                        : " << config.seed << "\n";
    std::cout << "amount_neural               : " << config.amount_neural << "\n";
    std::cout << "value_gamma                 : " << config.value_gamma << "\n";
    std::cout << "value_size_batch            : " << config.value_size_batch << "\n";
    std::cout << "value_min_amount_transition : " << config.value_min_amount_transition << "\n";
    std::cout << "value_update_intervale      : " << config.value_update_intervale << "\n";
    std::cout << "buffer_size                 : " << config.buffer_size << "\n";
    std::cout << "learning_rate               : " << config.learning_rate << "\n";
    std::cout << "\n";
}

void clear() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void delay(int millisecondes) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecondes));
}


void comparaison_matrix(Matrix const &result, Matrix const &expected, std::string const &nom) {

    std::ostringstream matExpectedStr;
    std::ostringstream matResultStr;

    for (Index i = 0; i < expected.get_row(); i++) {
        for (Index j = 0; j < expected.get_column(); j++) {
            std::ostringstream casee;
            casee << nom << " cellule (" << i << "," << j << ")";
            matExpectedStr << expected.get_value(i,j) << " ";
            matResultStr<< result.get_value(i,j) << " ";
        }
        matExpectedStr << std::endl;
        matResultStr << std::endl;
    }

    std::cout << "Matrice attendu :\n\n" << matExpectedStr.str() << "\n\nMatrice obtenu :\n\n" << matResultStr.str() << std::endl;
}

