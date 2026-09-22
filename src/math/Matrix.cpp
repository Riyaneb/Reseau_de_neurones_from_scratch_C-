#include "math/Matrix.hpp"
#include <cassert>

Index Matrix::check_size(Index l, Index c) {
    assert(l > 0 && c >0 && "Le nombre de ligne ou de colonne de la matrice est négatif ou nulle");
    return l*c;
}

Index Matrix::size_mat(Index l, Index c) const{
    return l*column + c;
}

Index Matrix::get_row() const {
    return row;
}

Index Matrix::get_column() const {
    return column;
}

const Scalar &Matrix::get_value(Index l, Index c) const {
    assert(l>=0 && l < row && c>=0 && c < column && "Erreur : Index incorrect");
    return mat[size_mat(l, c)];
}

Scalar &Matrix::get_value(Index l, Index c) {
    assert(l>=0 && l < row && c>=0 && c < column && "Erreur : Index incorrect");
    return mat[size_mat(l, c)];
}

Matrix& Matrix::operator+=(Matrix const &m) {
    assert(m.row == row && m.column == column && "Erreur : Les matrices n'ont pas la même dimension");
    for (Index i = 0; i < row*column; ++i) {
        mat[i] += m.mat[i];
    }
    return *this;
}

Matrix operator+(Matrix const &m1, Matrix const &m2) {
    Matrix result = Matrix(m1);
    result += m2;
    return result;
}

Matrix& Matrix::operator-=(Matrix const &m) {
    assert(m.row == row && m.column == column && "Erreur : Les matrices n'ont pas la même dimension");
    for (Index i = 0; i < row*column; ++i) {
        mat[i] -= m.mat[i];
    }
    return *this;
}

Matrix operator-(Matrix const &m1, Matrix const &m2) {
    Matrix result = Matrix(m1);
    result -= m2;
    return result;
}

Matrix& Matrix::hadamard(Matrix const &m) {
    assert(m.row == row && m.column == column && "Erreur : Les matrices n'ont pas la même dimension");
    for (Index i = 0; i < row*column; ++i) {
        mat[i] *= m.mat[i];
    }
    return *this;
}

Matrix hadamard(Matrix const &m1, Matrix const &m2) {
    Matrix result = Matrix(m1);
    result.hadamard(m2);
    return result;
}

Matrix& Matrix::operator*=(Scalar const &a) {
    for (Index i = 0; i < row*column; ++i) {
        mat[i] *= a;
    }
    return *this;
}

Matrix operator*(Matrix const &m, Scalar a) {
    Matrix result = Matrix(m);
    result *= a;
    return result;
}

Matrix operator*(Scalar a,Matrix const &m) {
    Matrix result = Matrix(m);
    result *= a;
    return result;
}

bool Matrix::isSquare() const {
    return row == column;
}

Matrix Matrix::transpose() const {
    Matrix result(column,row);
    for (Index i = 0; i < row; ++i) {
        for (Index j = 0; j < column; ++j) {
            result.get_value(j,i) = this->get_value(i,j);
        }
    }
    return result;
}

Matrix &Matrix::broadcast(Matrix const &biais) {
    assert(biais.row == 1 && biais.column == column && "Erreur : Dimension du biais incorrect");
    for (Index i = 0; i < row; ++i) {
        for (Index j = 0; j < column; ++j) {
            this->get_value(i,j) += biais.get_value(0,j);
        }
    }
    return *this;
}

Matrix broadcast(Matrix const &m, Matrix const &biais) {
    Matrix result = Matrix(m);
    result.broadcast(biais);
    return result;
}

Matrix Matrix::sum_row() const {
    Matrix result(1,column);
    for (Index i = 0; i < row; ++i) {
        for (Index j = 0; j < column; ++j) {
            result.get_value(0,j) += this->get_value(i,j);
        }
    }
    return result;
}

Matrix operator*(Matrix const &m1, Matrix const &m2) {
    assert(m1.get_column() == m2.get_row() && "Erreur : Dimension incorrecte pour la multiplication matricielle");
    Matrix result(m1.get_row(),m2.get_column(),0);

    for (Index i = 0; i < m1.get_row(); ++i) {
        for (Index j = 0; j < m2.get_column(); ++j) {
            for (Index k = 0; k < m1.get_column(); ++k) {
                result.get_value(i,j) += m1.get_value(i,k) * m2.get_value(k,j);
            }
        }
    }
    return result;
}


Matrix Matrix::matIdentity(Index n) {
    Matrix result(n,n,0);
    for (Index j=0;j<n;j++) {
        result.get_value(j,j) = 1.0;
    }
    return result;
}
