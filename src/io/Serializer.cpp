#include <string>
#include <fstream>
#include <iostream>
#include <limits>
#include <iomanip>
#include "nn/Network.hpp"
#include "nn/DenseLayer.hpp"

void save(Network &net, std::string const &filename) {
    std::ofstream f(filename.c_str());
    if (f) {
        f << std::setprecision(std::numeric_limits<Scalar>::max_digits10);
        PairParameters params = net.get_parameters();
        Index size = params.size();
        f << size << std::endl;
        for (Index k = 0; k < size; k++) {
            Matrix param = *(params[k].first);
            Index nRow = param.get_row();
            Index nCol = param.get_column();
            f << nRow << " " << nCol << std::endl;
            for (Index i = 0; i < nRow; i++) {
                for (Index j = 0; j < nCol; j++) {
                    f << param.get_value(i, j) << " ";
                }
            }
            f << std::endl;
        }
    }
    else {
        std::cerr << "Erreur dans la création du fichier " << filename << "\n";
        return;
    }
    f.close();
}

void load(Network &net, std::string const &filename) {
    std::ifstream f(filename.c_str());
    if (f) {
        PairParameters params = net.get_parameters();
        Index size = params.size();
        Index fileSize;
        f >> fileSize;
        if (size != fileSize) {
            std::cerr << "Erreur sur la taille du réseau de neurone";
            return;
        }
        else {
            for (Index k = 0; k < size; k++) {
                Matrix& param = *(params[k].first);
                Index row,col;
                f >> row >> col;
                if (row != param.get_row() || col != param.get_column()) {
                    std::cerr << "Erreur : La matrice " << k + 1 << " ne possède pas la bonne dimension" << std::endl;
                    return;
                }
                else {
                    Scalar temp;
                    for (int i = 0; i < row; i++) {
                        for (int j = 0; j < col; j++) {
                            f >> temp;
                            param.get_value(i, j) = temp;
                        }
                    }
                }
            }
        }
    }
    else {
        std::cerr << "Erreur dans l'ouverture du fichier " << filename << "\n";
        return;
    }
    f.close();
}
