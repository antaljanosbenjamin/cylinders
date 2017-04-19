//
// Created by kovi on 4/16/17.
//

#include "Number.h"
#include <cmath>

Number::Number()
        : value( 0.0f ) {}

Number::Number( const double &doubleValue )
        : value( doubleValue ) {}

// Number operators
bool Number::operator==( const Number &other ) const {
    return ( value < other.value + EPSZILON && value > other.value - EPSZILON );
}

bool Number::operator!=( const Number &other ) const {
    return !( *this == other );
}

bool Number::operator>( const Number &other ) const {
    return value >= other.value + EPSZILON;
}

bool Number::operator<( const Number &other ) const {
    return value <= other.value - EPSZILON;
}

bool Number::operator>=( const Number &other ) const {
    return !operator<( other );
}

bool Number::operator<=( const Number &other ) const {
    return !operator>( other );
}

Number Number::operator+( const Number &other ) const {
    return Number( value + other.value );
}

Number Number::operator-( const Number &other ) const {
    return Number( value - other.value );
}

Number Number::operator*( const Number &other ) const {
    return Number( value * other.value );
}

Number Number::operator/( const Number &other ) const {
    return Number( value / other.value );
}

Number &Number::operator+=( const Number &other ) {
    value += other.value;
    return ( *this );
}

Number &Number::operator-=( const Number &other ) {
    value -= other.value;
    return ( *this );
}

Number &Number::operator*=( const Number &other ) {
    value *= other.value;
    return ( *this );
}

Number &Number::operator/=( const Number &other ) {
    value /= other.value;
    return ( *this );
}

Number Number::operator-() const {
    return Number( -value );
}

// double operators
bool Number::operator==( const double &doubleValue ) const {
    return *this == Number( doubleValue );
}

bool Number::operator!=( const double &doubleValue ) const {
    return *this != Number( doubleValue );
}

bool Number::operator>( const double &doubleValue ) const {
    return *this > Number( doubleValue );
}

bool Number::operator<( const double &doubleValue ) const {
    return *this < Number( doubleValue );
}

bool Number::operator>=( const double &doubleValue ) const {
    return *this >= Number( doubleValue );
}

bool Number::operator<=( const double &doubleValue ) const {
    return *this <= Number( doubleValue );
}


Number Number::operator+( const double &doubleValue ) const {
    return *this + Number ( doubleValue );
}

Number Number::operator-( const double &doubleValue ) const {
    return *this - Number ( doubleValue );
}

Number Number::operator*( const double &doubleValue ) const {
    return *this * Number ( doubleValue );
}

Number Number::operator/( const double &doubleValue ) const {
    return *this / Number ( doubleValue );
}

Number &Number::operator+=( const double &doubleValue ) {
    return *this += Number ( doubleValue );
}

Number &Number::operator-=( const double &doubleValue ) {
    return *this -= Number ( doubleValue );
}

Number &Number::operator*=( const double &doubleValue ) {
    return *this *= Number ( doubleValue );
}

Number &Number::operator/=( const double &doubleValue ) {
    return *this /= Number ( doubleValue );
}

double Number::operator=( const double &doubleValue ) {
    *this = Number ( doubleValue );
    return doubleValue;
}

Number Number::pow( const Number base, const Number exponent ) {
    return Number( std::pow( base.value, exponent.value ));
}

Number Number::pow( const Number base, const double exponent ) {
    return Number( std::pow( base.value, exponent ));
}

Number Number::sqrt( const Number x ) {
    return Number( std::sqrt( x.value ));
}

Number Number::abs( const Number x ) {
    return Number( fabs( x.value ));
}

Number Number::sin( const Number x ) {
    return Number( std::sin( x.value ));
}

Number Number::cos( const Number x ) {
    return Number( std::cos( x.value ));
}

// double operators
Number operator+( const double &lhs, const Number &rhs ) {
    return Number( lhs ) + rhs;
}

Number operator-( const double &lhs, const Number &rhs ) {
    return Number( lhs ) - rhs;
}

Number operator*( const double &lhs, const Number &rhs ) {
    return Number( lhs ) * rhs;
}

Number operator/( const double &lhs, const Number &rhs ) {
    return Number( lhs ) / rhs;
}