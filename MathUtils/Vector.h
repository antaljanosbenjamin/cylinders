//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_VECTOR_H
#define CYLINDERS_VECTOR_H

#include "Number.h"
#include <cmath>

struct Vector {

    Number m_x, m_y, m_z;

    const Number &getX() const;

    void setX( const Number &x );

    const Number &getY() const;

    void setY( const Number &y );

    const Number &getZ() const;

    void setZ( const Number &z );

    Vector();

    Vector( const Number x0, const Number y0, const Number z0 = Number( 0 ));

    Vector( const double x0, const double y0, const double z0 = 0.0f );

    Vector operator*( const Number &number ) const;

    Vector operator/( const Number &number ) const;

    Vector operator*( const double &doubleValue ) const;

    Vector operator/( const double &doubleValue ) const;

    Vector operator+( const Vector &v ) const;

    Vector operator-( const Vector &v ) const;

    // dot product
    Number operator*( const Vector &v ) const;

    // cross product
    Vector operator%( const Vector &v ) const;

    // cos+ const
    Number operator&( const Vector &v ) const;

    Number length() const;

    Number getDistance( const Vector &v ) const;

    Vector getNormalized() const;

    Vector rotateByZ( Number fi );

    Vector rotateByY( Number fi );
};

Vector operator*( const Number &s, const Vector &v );

Vector operator*( const double &s, const Vector &v );


#endif //CYLINDERS_VECTOR_H
