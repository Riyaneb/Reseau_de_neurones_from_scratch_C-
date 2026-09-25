#include "nn/Optimizers.hpp"
#include <cassert>

void SGD::update_parameters(PairParameters &parameters) const {
    PairParameters::iterator it;
    for (it = parameters.begin(); it != parameters.end(); ++it) {
        assert(it->first->get_row() == it->second->get_row() && it->first->get_column() == it->second->get_column() && "Erreur : Paramètre n'ayant pas la même dimension que leur gradient");
        *(it->first) -= taux * *(it->second);
    }
}
