#ifndef RESEAU_DE_NEURONES_FROM_SCRATCH_C_MATRIX_HPP
#define RESEAU_DE_NEURONES_FROM_SCRATCH_C_MATRIX_HPP

#include "math/Types.hpp"
#include <vector>
#include <cassert>

class Matrix {
public:
    Matrix(Index l,Index c,Scalar init_value=0): row(l), column(c), mat(check_size(l,c), init_value) {}
    Index get_row() const;
    Index get_column() const;
    const Scalar &get_value(Index l, Index c) const;
    Scalar &get_value(Index l, Index c);

private:
    static Index check_size(Index l, Index c);
    Index row;
    Index column;
    std::vector<Scalar> mat;
    Index size_mat(Index l, Index c) const;
};

#endif //RESEAU_DE_NEURONES_FROM_SCRATCH_C_MATRIX_HPP
