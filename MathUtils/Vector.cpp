//
// Created by kovi on 4/16/17.
//

#include "Vector.h"


Vector::Vector() {
    m_x = m_y = m_z = 0;
}

Vector::Vector( const Number x0, const Number y0, const Number z0 )
        : m_x( x0 ), m_y( y0 ), m_z( z0 ) {};

Vector::Vector( const double x0, const double y0, const double z0 )
        : m_x( x0 ), m_y( y0 ), m_z( z0 ) {};

Vector Vector::operator+( const Vector &v ) const {
    return Vector( m_x + v.m_x, m_y + v.m_y, m_z + v.m_z );
}

Vector Vector::operator-( const Vector &v ) const {
    return Vector( m_x - v.m_x, m_y - v.m_y, m_z - v.m_z );
}

Number Vector::operator*( const Vector &v ) const {    // dot product
    return ( m_x * v.m_x + m_y * v.m_y + m_z * v.m_z );
}

Vector Vector::operator%( const Vector &v ) const {    // cross product
    return Vector( m_y * v.m_z - m_z * v.m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x );
}

// cos+
Number Vector::operator&( const Vector &v ) const {
    Number ret = operator*( v );
    if( ret < 0.0 )
        return Number( 0 );
    else
        return ret;
}

Vector Vector::operator*( const Number &number ) const {
    return Vector( m_x * number, m_y * number, m_z * number );
}

Vector Vector::operator/( const Number &number ) const {
    return Vector( m_x / number, m_y / number, m_z / number );
}

Vector Vector::operator*( const double &doubleValue ) const {
    return *this * Number( doubleValue );
}

Vector Vector::operator/( const double &doubleValue ) const {
    return *this / Number( doubleValue );
}

Number Vector::length() const { return nsqrt( m_x * m_x + m_y * m_y + m_z * m_z ); };

Number Vector::getDistance( const Vector &v ) const {
    return npow(( npow( m_x - v.m_x, 2 ) + npow( m_y - v.m_y, 2 ) + npow( m_z - v.m_z, 2 )), 0.5f );
};

Vector Vector::getNormalized() const {
    return ( *this ) / this->length();
};

Vector Vector::rotateByZ( Number fi ) {
    return Vector( m_x * ncos( fi ) - m_y * nsin( fi ), m_x * nsin( fi ) + m_y * ncos( fi ), Number( 0 ) );
};

Vector Vector::rotateByY( Number fi ) {
    return Vector( m_z * nsin( fi ) + m_x * ncos( fi ), m_y, m_z * ncos( fi ) - m_x * nsin( fi ));
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

Vector operator*( const double &s, const Vector &v ) {
    return v * Number( s );
}