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

    Vector( Number x0, Number y0, Number z0 = 0 );

    Vector operator*( const Number &a );

    Vector operator+( const Vector &v );

    Vector operator-( const Vector &v );

    // dot product
    Number operator*( const Vector &v );

    Vector operator/( Number a );

    // cross product
    Vector operator%( const Vector v );

    // cos+
    Number operator&( const Vector v );

    Number length();

    Number getDistance( Vector v );

    Vector getNormalized();

    Vector rotateByZ( Number fi );

    Vector rotateByY( Number fi );
};


Vector operator*( const Number &s, const Vector &v );


#endif //CYLINDERS_VECTOR_H
