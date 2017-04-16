//
// Created by kovi on 4/16/17.
//

#include "Vector.h"


Vector::Vector() {
    m_x = m_y = m_z = 0;
}

Vector::Vector( Number x0, Number y0, Number z0 )
        : m_x( x0 ), m_y( y0 ), m_z( z0 ) {};

Vector Vector::operator*( const Number &a ) {
    return Vector( m_x * a, m_y * a, m_z * a );
}

Vector Vector::operator+( const Vector &v ) {
    return Vector( m_x + v.m_x, m_y + v.m_y, m_z + v.m_z );
}

Vector Vector::operator-( const Vector &v ) {
    return Vector( m_x - v.m_x, m_y - v.m_y, m_z - v.m_z );
}

Number Vector::operator*( const Vector &v ) {    // dot product
    return ( m_x * v.m_x + m_y * v.m_y + m_z * v.m_z );
}

Vector Vector::operator/( Number a ) {
    return Vector( m_x / a, m_y / a, m_z / a );
}

Vector Vector::operator%( const Vector v ) {    // cross product
    return Vector( m_y * v.m_z - m_z * v.m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x );
}

// cos+
Number Vector::operator&( const Vector v ) {
    Number ret = operator*( v );
    if( ret < 0 )
        return 0;
    else
        return ret;
}

Number Vector::length() { return sqrt( m_x * m_x + m_y * m_y + m_z * m_z ); };

Number Vector::getDistance( Vector v ) {
    return pow(( pow( m_x - v.m_x, 2 ) + pow( m_y - v.m_y, 2 ) + pow( m_z - v.m_z, 2 )), 0.5f );
};

Vector Vector::getNormalized() {
    return ( *this ) / this->length();
};

Vector Vector::rotateByZ( Number fi ) {
    return Vector( m_x * cos( fi ) - m_y * sin( fi ), m_x * sin( fi ) + m_y * cos( fi ), 0.0f );
};

Vector Vector::rotateByY( Number fi ) {
    return Vector( m_z * sin( fi ) + m_x * cos( fi ), m_y, m_z * cos( fi ) - m_x * sin( fi ));
}

const Number &Vector::getX() const {
    return m_x;
}

void Vector::setX( const Number &x ) {
    m_x = x;
}

const Number &Vector::getY() const {
    return m_y;
}

void Vector::setY( const Number &y ) {
    m_y = y;
}

const Number &Vector::getZ() const {
    return m_z;
}

void Vector::setZ( const Number &z ) {
    m_z = z;
};

Vector operator*( const Number &s, const Vector &v ) {
    return Vector( v.m_x * s, v.m_y * s, v.m_z * s );
}