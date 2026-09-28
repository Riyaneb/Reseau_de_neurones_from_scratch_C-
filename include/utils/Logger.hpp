#ifndef RESEAUDENEURONEFROMSCRATCH_LOGGER_HPP
#define RESEAUDENEURONEFROMSCRATCH_LOGGER_HPP
#include "rl/DQNAgent.hpp"


void print_configuration(ConfigurationAgent const &config);
void clear();
void delay(int millisecondes);
void comparaison_matrix(Matrix const &result, Matrix const &expected, std::string const &nom);

#endif //RESEAUDENEURONEFROMSCRATCH_LOGGER_HPP
