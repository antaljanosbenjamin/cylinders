//
// Created by kovi on 4/16/17.
//

#include "Matrix.h"


void Matrix::clear() { // a mátrixelemek törlése
    matrix[0][0] = matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[1][3] =
    matrix[2][0] = matrix[2][1] = matrix[2][2] = matrix[2][3] = matrix[3][0] = matrix[3][1] = matrix[3][2] = matrix[3][3] = Number( 0.0f );
}

void Matrix::loadIdentity() { // a mátrix legyen egységmátrix
    clear();
    matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
}

Matrix Matrix::operator+( const Matrix &mat ) { // mátrix összeadás
    Matrix result;
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ ) result.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
    return result;
}

Matrix Matrix::operator*( const Matrix &mat ) { // mátrixok szorzása
    Matrix result;
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ ){
            result.matrix[i][j] = 0;
            for( int k = 0; k < 4; k++ ) result.matrix[i][j] += matrix[i][k] * mat.matrix[k][j];
        }
    return result;
}

Vector Matrix::operator*( const Vector v ) { // Vektor-mátrix szorzás
    Number Xh = matrix[0][0] * v.x + matrix[0][1] * v.m_y + matrix[0][2] * v.m_z + matrix[0][3];
    Number Yh = matrix[1][0] * v.x + matrix[1][1] * v.m_y + matrix[1][2] * v.m_z + matrix[1][3];
    Number Zh = matrix[2][0] * v.x + matrix[2][1] * v.m_y + matrix[2][2] * v.m_z + matrix[2][3];
    Number h = matrix[3][0] * v.x + matrix[3][1] * v.m_y + matrix[3][2] * v.m_z + matrix[3][3];
    return Vector( Xh / h, Yh / h, Zh / h );
}

Vector operator*( const Vector v, const Matrix &mat ) { // Vektor-mátrix szorzás
    Number Xh = mat.matrix[0][0] * v.x + mat.matrix[1][0] * v.m_y + mat.matrix[2][0] * v.m_z + mat.matrix[3][0];
    Number Yh = mat.matrix[0][1] * v.x + mat.matrix[1][1] * v.m_y + mat.matrix[2][1] * v.m_z + mat.matrix[3][1];
    Number Zh = mat.matrix[0][2] * v.x + mat.matrix[1][2] * v.m_y + mat.matrix[2][2] * v.m_z + mat.matrix[3][2];
    Number h = mat.matrix[0][3] * v.x + mat.matrix[1][3] * v.m_y + mat.matrix[2][3] * v.m_z + mat.matrix[3][3];
    return Vector( Xh / h, Yh / h, Zh / h );
};