#include "math/Matrix.hpp"
#include "TestRunner.hpp"
#include <sstream>

void test_indexation(TestRunner &runner, Matrix &matrix) {
    std::ostringstream MatExpected;
    for (Index i = 0; i < matrix.get_row(); i++) {
        for (Index j = 0; j < matrix.get_column(); j++) {
            matrix.get_value(i,j) = 10*i+j;
            MatExpected << 10*i+j << " ";
        }
        MatExpected << std::endl;
    }

    std::ostringstream strMat;
    for (Index i = 0; i < matrix.get_row(); i++) {
        for (Index j = 0; j < matrix.get_column(); j++) {
            std::ostringstream nom;
            Scalar cas = 10*i+j;
            nom << "cellule (" << i << "," << j << ")";
            strMat << matrix.get_value(i,j) << " ";
            runner.check_values(cas, matrix.get_value(i,j), nom.str());
        }
        strMat << std::endl;
    }

    std::cout << "Matrice attendu : \n\n " << MatExpected.str() << "\n\nMatrice obtenu : \n\n" << strMat.str() << std::endl;
}

void test_matrice(TestRunner& runner) {
    Matrix matriceA(3,2,7.0);
    Matrix matriceB(2,3);
    //Matrix matriceC(3,3);

    runner.section("Test dimension");
    runner.check_values(2,matriceA.get_column(), "Test colonnes");
    runner.check_values(3,matriceA.get_row(), "Test lignes");

    runner.section("Test remplissage");
    runner.check_values(7.0,matriceA.get_value(1,1),"Valeurs quelconque");

    runner.section("Test Indexation A");
    test_indexation(runner, matriceA);

    runner.section("Test Indexation B");
    test_indexation(runner, matriceB);

}


