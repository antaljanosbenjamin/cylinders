//
// Created by kovi on 4/16/17.
//

#include "Matrix.h"


void Matrix::clear() { // a mátrixelemek törlése
    m_matrix[0][0] = m_matrix[0][1] = m_matrix[0][2] = m_matrix[0][3] = m_matrix[1][0] = m_matrix[1][1] = m_matrix[1][2] = m_matrix[1][3] =
    m_matrix[2][0] = m_matrix[2][1] = m_matrix[2][2] = m_matrix[2][3] = m_matrix[3][0] = m_matrix[3][1] = m_matrix[3][2] = m_matrix[3][3] = Number( 0.0f );
}

void Matrix::loadIdentity() { // a mátrix legyen egységmátrix
    clear();
    m_matrix[0][0] = m_matrix[1][1] = m_matrix[2][2] = m_matrix[3][3] = 1;
}

Matrix Matrix::operator+( const Matrix &mat ) { // mátrix összeadás
    Matrix result;
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ ) result.m_matrix[i][j] = m_matrix[i][j] + mat.m_matrix[i][j];
    return result;
}

Matrix Matrix::operator*( const Matrix &mat ) { // mátrixok szorzása
    Matrix result;
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ ){
            result.m_matrix[i][j] = 0;
            for( int k = 0; k < 4; k++ ) result.m_matrix[i][j] += m_matrix[i][k] * mat.m_matrix[k][j];
        }
    return result;
}

Vector Matrix::operator*( const Vector v ) { // Vektor-mátrix szorzás
    Number Xh = m_matrix[0][0] * v.m_x + m_matrix[0][1] * v.m_y + m_matrix[0][2] * v.m_z + m_matrix[0][3];
    Number Yh = m_matrix[1][0] * v.m_x + m_matrix[1][1] * v.m_y + m_matrix[1][2] * v.m_z + m_matrix[1][3];
    Number Zh = m_matrix[2][0] * v.m_x + m_matrix[2][1] * v.m_y + m_matrix[2][2] * v.m_z + m_matrix[2][3];
    Number h = m_matrix[3][0] * v.m_x + m_matrix[3][1] * v.m_y + m_matrix[3][2] * v.m_z + m_matrix[3][3];
    return Vector( Xh / h, Yh / h, Zh / h );
}

Vector operator*( const Vector v, const Matrix &mat ) { // Vektor-mátrix szorzás
    Number Xh = mat.m_matrix[0][0] * v.m_x + mat.m_matrix[1][0] * v.m_y + mat.m_matrix[2][0] * v.m_z + mat.m_matrix[3][0];
    Number Yh = mat.m_matrix[0][1] * v.m_x + mat.m_matrix[1][1] * v.m_y + mat.m_matrix[2][1] * v.m_z + mat.m_matrix[3][1];
    Number Zh = mat.m_matrix[0][2] * v.m_x + mat.m_matrix[1][2] * v.m_y + mat.m_matrix[2][2] * v.m_z + mat.m_matrix[3][2];
    Number h = mat.m_matrix[0][3] * v.m_x + mat.m_matrix[1][3] * v.m_y + mat.m_matrix[2][3] * v.m_z + mat.m_matrix[3][3];
    return Vector( Xh / h, Yh / h, Zh / h );
};