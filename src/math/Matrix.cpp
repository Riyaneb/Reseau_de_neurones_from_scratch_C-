#include "math/Matrix.hpp"

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
