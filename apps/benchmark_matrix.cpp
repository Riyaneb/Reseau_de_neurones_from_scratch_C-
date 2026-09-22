#include "math/Matrix.hpp"
#include "utils/Timer.hpp"
#include <iostream>

using namespace std;

void bench() {

}

int main() {
    Matrix A(600,600);
    Matrix B(600,600);
    for (Index i = 0; i < 600; i++) {
        for (Index j = 0; j < 600; j++) {
            A.get_value(i,j) = i*17+3*j+7;
            B.get_value(i,j) = i*7+33*j+12;
        }
    }
    Timer t;
    Matrix C = A*B;
    cout << "Temps pour faire le produit matricielle d'une matrice 600x600 avec une matrice 600x600 : " << t.elapsed() << "s" << endl;
    return 0;
}