#include "math/Matrix.hpp"
#include "TestRunner.hpp"
#include <sstream>

void comparaison_matrix(TestRunner &runner, Matrix const &result, Matrix const &expected, std::string const &nom) {
    std::ostringstream nCo;
    nCo << nom << " : Test dimension colonne";
    std::ostringstream nRow;
    nRow << nom << " : Test dimension ligne";
    runner.check_values(expected.get_row(), result.get_row(), nRow.str());
    runner.check_values(expected.get_column(),result.get_column(),nCo.str());
    if (expected.get_row() != result.get_row() || expected.get_column() != result.get_column()) {
        return;
    }

    std::ostringstream matExpectedStr;
    std::ostringstream matResultStr;

    for (Index i = 0; i < expected.get_row(); i++) {
        for (Index j = 0; j < expected.get_column(); j++) {
            std::ostringstream casee;
            casee << nom << " cellule (" << i << "," << j << ")";
            runner.check_values(expected.get_value(i,j), result.get_value(i,j), casee.str());
            matExpectedStr << expected.get_value(i,j) << " ";
            matResultStr<< result.get_value(i,j) << " ";
        }
        matExpectedStr << std::endl;
        matResultStr << std::endl;
    }

    std::cout << "Matrice attendu :\n\n " << matExpectedStr.str() << "\n\nMatrice obtenu : \n\n" << matResultStr.str() << std::endl;
}

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

    std::cout << "Matrice attendu :\n\n " << MatExpected.str() << "\n\nMatrice obtenu : \n\n" << strMat.str() << std::endl;
}

void test_addition(TestRunner &runner) {

    Matrix A(3,2);
    Matrix B(3,2);
    Matrix expected(3,2);

    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = 10*i + j;
            B.get_value(i,j) = 100*i + j;
            expected.get_value(i,j) = (10*i + j) + (100*i + j);
        }
    }

    Matrix copieA(A);
    Matrix copieB(B);
    Matrix C = A+B;
    comparaison_matrix(runner, C,expected,"Test addition");
    comparaison_matrix(runner, A,copieA,"Test intégrité addition A");
    comparaison_matrix(runner, B,copieB,"Test intégrité addition B");
}

void test_soustraction(TestRunner &runner) {

    Matrix A(3,2);
    Matrix B(3,2);
    Matrix expected(3,2);

    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = 10*i + 3*j;
            B.get_value(i,j) = 100*i + 2*j;
            expected.get_value(i,j) = (10*i + 3*j) - (100*i + 2*j);
        }
    }
    Matrix copieA(A);
    Matrix copieB(B);
    Matrix C = A-B;
    comparaison_matrix(runner, C,expected,"Test soustraction");
    comparaison_matrix(runner, A,copieA,"Test intégrité soustraction A");
    comparaison_matrix(runner, B,copieB,"Test intégrité soustractionB");
}


void test_multiplication_scalaire(TestRunner &runner) {
    Matrix A(3,2);
    Scalar n(2.0);
    Matrix expected(3,2);

    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = 10*i + j;
            expected.get_value(i,j) = (10*i + j)*n;
        }
    }

    Matrix copieA(A);
    Matrix C = A*n;
    Matrix D = n*A;
    comparaison_matrix(runner, C,expected,"Test multiplication par scalaire 1");
    comparaison_matrix(runner, D,expected,"Test multiplication par scalaire 2");
    comparaison_matrix(runner, A,copieA,"Test intégrité multiplication par scalaire A");

}

void test_hadamard(TestRunner &runner) {
    Matrix A(3,2);
    Matrix B(3,2);
    Matrix expected(3,2);

    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = 10*i + j;
            B.get_value(i,j) = 100*i + 2*j;
            expected.get_value(i,j) = (10*i + j)*(100*i + 2*j);
        }
    }

    Matrix copieA(A);
    Matrix copieB(B);
    Matrix C = hadamard(A,B);
    comparaison_matrix(runner, C,expected,"Test multiplication Hadamard");
    comparaison_matrix(runner, A,copieA,"Test intégrité multiplication Hadamard A");
    comparaison_matrix(runner, B,copieB,"Test intégrité multiplication Hadamard B");

}

void test_transpose(TestRunner &runner) {
    Matrix A(3,2);
    if (A.isSquare()) {
        std::cout << "A est une matrice carré" << std::endl;
    }
    else {
        std::cout << "A n'est pas une matrice carré" << std::endl;
    }
    Matrix expected(2,3);
    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = 10*i + j;
        }
    }

    for (Index i = 0; i < expected.get_row(); i++) {
        for (Index j = 0; j < expected.get_column(); j++) {
            expected.get_value(i,j) = 10*j + i;
        }
    }

    Matrix copieA(A);
    Matrix C = A.transpose();

    comparaison_matrix(runner, C,expected,"Test transposé");
    Matrix D = C.transpose();
    comparaison_matrix(runner, D,A,"Test transpose de la transposé");
    comparaison_matrix(runner, A,copieA,"Test intégrité transposé");
}

void test_broadcast(TestRunner &runner) {
    Matrix A(3,2);
    Matrix biais(1,2);
    Matrix expected(3,2);

    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = 10*i + j + 1;
            biais.get_value(0,j) = j+1;
            expected.get_value(i,j) = (10*i + j + 1)+(j+1);
        }
    }

    Matrix copieA(A);
    Matrix cA(A);
    Matrix copieB(biais);
    Matrix C = broadcast(A,biais);
    Matrix D = copieA.broadcast(biais);

    comparaison_matrix(runner, C,expected,"Test diffusion 1");
    comparaison_matrix(runner, D,expected,"Test diffusion 2");
    comparaison_matrix(runner, A,cA,"Test intégrité diffusion A");
    comparaison_matrix(runner, biais,copieB,"Test intégrité diffusion B");
}

void test_sum_axes(TestRunner &runner) {
    Matrix A(3,2);
    Matrix expected(1,2);
    expected.get_value(0,0) = 9;
    expected.get_value(0,1) = 12;
    int cpt = 1;
    for (Index i = 0; i < A.get_row(); i++) {
        for (Index j = 0; j < A.get_column(); j++) {
            A.get_value(i,j) = cpt;
            cpt++;
        }
    }
    Matrix copieA(A);
    Matrix C = A.sum_row();
    comparaison_matrix(runner, C,expected,"Test somme des lignes");
    comparaison_matrix(runner, A,copieA,"Test intégrité somme des lignes");
}

void test_matrice(TestRunner& runner) {
    Scalar const n1 = 7.0;
    Matrix matriceA(3,2,n1);
    Matrix matriceB(2,3);

    runner.section("Test dimension");
    runner.check_values(2,matriceA.get_column(), "Test colonnes");
    runner.check_values(3,matriceA.get_row(), "Test lignes");

    runner.section("Test remplissage");
    runner.check_values(n1,matriceA.get_value(1,1),"Valeurs quelconque");

    runner.section("Test Indexation A");
    test_indexation(runner, matriceA);

    runner.section("Test Indexation B");
    test_indexation(runner, matriceB);

    runner.section("Test addition de deux matrices");
    test_addition(runner);

    runner.section("Test soustraction de deux matrices");
    test_soustraction(runner);

    runner.section("Test multiplication par scalaire");
    test_multiplication_scalaire(runner);

    runner.section("Test multiplication Hadamard");
    test_hadamard(runner);

    runner.section("Test transposé");
    test_transpose(runner);

    runner.section("Test diffusion");
    test_broadcast(runner);

    runner.section("Test somme des lignes");
    test_sum_axes(runner);
}


