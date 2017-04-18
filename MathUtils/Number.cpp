//
// Created by kovi on 4/16/17.
//

#include "Number.h"

Number::Number()
        : value( 0.0f ) {}

Number::Number( const int &intValue )
        : value( intValue ) {}

Number::Number( const float &floatValue )
        : value( floatValue ) {}

Number::Number( const double &doubleValue )
        : value( doubleValue ) {}

// Number operators
bool Number::operator==( const Number &other ) {
    return ( value < other.value + EPSZILON && value > other.value - EPSZILON );
}

bool Number::operator>( const Number &other ) {
    return value >= other.value + EPSZILON;
}

bool Number::operator<( const Number &other ) {
    return value <= other.value - EPSZILON;
}

bool Number::operator>=( const Number &other ) {
    return !operator<( other );
}

bool Number::operator<=( const Number &other ) {
    return !operator>( other );
}

Number Number::operator+( const Number &other ) {
    return Number( value + other.value );
}

Number Number::operator-( const Number &other ) {
    return Number( value - other.value );
}

Number Number::operator*( const Number &other ) {
    return Number( value * other.value );
}

Number Number::operator/( const Number &other ) {
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


// int operators
bool Number::operator==( const int &intValue ) {
    return ( value < intValue + EPSZILON && value > intValue - EPSZILON );
}

bool Number::operator>( const int &intValue ) {
    return value >= intValue + EPSZILON;
}

bool Number::operator<( const int &intValue ) {
    return value <= intValue - EPSZILON;
}

bool Number::operator>=( const int &intValue ) {
    return !operator<( intValue );
}

bool Number::operator<=( const int &intValue ) {
    return !operator>( intValue );
}

int Number::operator=( const int &intValue ) {
    value = intValue;
    return intValue;
}

// double operators
Number Number::operator+( const double &doubleValue ) {
    return Number( value + doubleValue );
}

Number Number::operator-( const double &doubleValue ) {
    return Number( value - doubleValue );
}

Number Number::operator*( const double &doubleValue ) {
    return Number( value * doubleValue );
}

Number Number::operator/( const double &doubleValue ) {
    return Number( value / doubleValue );
}

Number &Number::operator+=( const double &doubleValue ) {
    value += doubleValue;
    return ( *this );
}

Number &Number::operator-=( const double &doubleValue ) {
    value -= doubleValue;
    return ( *this );
}

Number &Number::operator*=( const double &doubleValue ) {
    value *= doubleValue;
    return ( *this );
}

Number &Number::operator/=( const double &doubleValue ) {
    value /= doubleValue;
    return ( *this );
}


float Number::operator=( const float &floatValue ) {
    value = floatValue;
    return floatValue;
}

double Number::operator=( const double &doubleValue ) {
    value = doubleValue;
    return doubleValue;
}

Number::operator float() const {
    return value;
}