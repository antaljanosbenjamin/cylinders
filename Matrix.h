//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_MATRIX_H
#define CYLINDERS_MATRIX_H

#include "Vector.h"

struct Matrix {
    //===============================================================
    Number m_matrix[4][4];

    void clear();

    void loadIdentity();

    Matrix operator+( const Matrix &mat );


    Matrix operator*( const Matrix &mat );

    Vector operator*( const Vector v );
};

Vector operator*( const Vector v, const Matrix &mat );


#endif //CYLINDERS_MATRIX_H
