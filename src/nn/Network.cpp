#include "nn/Network.hpp"


void Network::add(std::unique_ptr<Layer> layer) {
    assert(layer != nullptr && "Erreur : Le pointeur est nul");
    if (!layers.empty()) {
        assert(layer->nInput() == layers.back()->nOutput() && "Erreur : Le nombre d'entrée de la nouvelle couche ne correspond pas au nombre de sortie de la dernière couche");
    }
    layers.push_back(std::move(layer));
}

Matrix Network::forward(Matrix const &X) {
    assert(!layers.empty() && "Erreur : Le réseau est vide");
    assert(X.get_column() == layers[0]->nInput() && "Erreur : Dimension de l'entrée incorrecte pour ce réseau");
    Matrix result = X;
    std::vector<std::unique_ptr<Layer>>::iterator it;
    for (it = layers.begin(); it != layers.end(); ++it) {
        result = (*it)->forward(result);
    }
    return result;
}

Matrix Network::backward(Matrix const &gradLoss) {
    assert(!layers.empty() && "Erreur : Le réseau est vide");
    assert(layers.back()->nOutput() == gradLoss.get_column() && "Erreur : Dimension de sortie incorrecte pour ce réseau");
    Matrix result = gradLoss;
    std::vector<std::unique_ptr<Layer>>::reverse_iterator it;
    for (it = layers.rbegin(); it != layers.rend(); ++it) {
        result = (*it)->backward(result);
    }
    return result;
}


