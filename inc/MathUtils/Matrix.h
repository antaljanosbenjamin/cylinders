#pragma once

#include "MathUtils/Vector.h"

struct Matrix {
    Number matrix[4][4];

    void clear();

    void loadIdentity();

    Matrix operator+(const Matrix &mat);

    Matrix operator*(const Matrix &mat);

    Vector operator*(const Vector v);
};

Vector operator*(const Vector v, const Matrix &mat);
