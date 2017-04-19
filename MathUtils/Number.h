//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_NUMBER_H
#define CYLINDERS_NUMBER_H


struct Number {

    typedef float NumberValue;
    NumberValue value;

    Number();

    explicit Number( const int &intValue );

    explicit Number( const float &floatValue );

    explicit Number( const double &doubleValue );

    // Number operators
    bool operator==( const Number &other ) const;

    bool operator!=( const Number &other ) const;

    bool operator>( const Number &other ) const;

    bool operator<( const Number &other ) const;

    bool operator>=( const Number &other ) const;

    bool operator<=( const Number &other ) const;

    Number operator+( const Number &other ) const;

    Number operator-( const Number &other ) const;

    Number operator*( const Number &other ) const;

    Number operator/( const Number &other ) const;

    Number &operator+=( const Number &other );

    Number &operator-=( const Number &other );

    Number &operator*=( const Number &other );

    Number &operator/=( const Number &other );

    Number operator-() const;

    // double operators
    bool operator==( const double &doubleValue ) const;

    bool operator!=( const double &doubleValue ) const;

    bool operator>( const double &doubleValue ) const;

    bool operator<( const double &doubleValue ) const;

    bool operator>=( const double &doubleValue ) const;

    bool operator<=( const double &doubleValue ) const;
    
    Number operator+( const double &doubleValue ) const;

    Number operator-( const double &doubleValue ) const;

    Number operator*( const double &doubleValue ) const;

    Number operator/( const double &doubleValue ) const;

    Number &operator+=( const double &doubleValue );

    Number &operator-=( const double &doubleValue );

    Number &operator*=( const double &doubleValue );

    Number &operator/=( const double &doubleValue );

    double operator=( const double &doubleValue );

    // Aritmetic function
    static Number pow( const Number base, const Number exponent );

    static Number pow( const Number base, const float exponent );

    static Number sqrt( const Number x );

    static Number abs( const Number x );

    static Number cos( const Number x );

    static Number sin( const Number x );

#define nsqrt( X ) Number::sqrt( X )
#define npow( BASE, EXPONENT ) Number::pow( BASE, EXPONENT )
#define nabs( X ) Number::abs( X )
#define ncos( X ) Number::cos( X )
#define nsin( X ) Number::sin( X )


private:
    static constexpr NumberValue EPSZILON = 0.000025f;
};
// double operators
Number operator+( const double &lhs, const Number &rhs );

Number operator-( const double &lhs, const Number &rhs );

Number operator*( const double &lhs, const Number &rhs );

Number operator/( const double &lhs, const Number &rhs );

#endif //CYLINDERS_NUMBER_H
