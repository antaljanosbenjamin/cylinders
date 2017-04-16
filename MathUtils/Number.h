//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_NUMBER_H
#define CYLINDERS_NUMBER_H


struct Number {

    typedef float NumberValue;
    NumberValue value;

    Number();

    Number( const int &intValue );

    Number( const float &floatValue );

    Number( const double &doubleValue );

    // Number operators
    bool operator==( const Number &other );

    bool operator>( const Number &other );

    bool operator<( const Number &other );

    bool operator>=( const Number &other );

    bool operator<=( const Number &other );

    Number operator+( const Number &other );

    Number operator-( const Number &other );

    Number operator*( const Number &other );

    Number operator/( const Number &other );

    Number &operator+=( const Number &other );

    Number &operator-=( const Number &other );

    Number &operator*=( const Number &other );

    Number &operator/=( const Number &other );

    // int operators
    int operator=( const int &intValue );

    bool operator==( const int &intValue );

    bool operator>( const int &intValue );

    bool operator<( const int &intValue );

    bool operator>=( const int &intValue );

    bool operator<=( const int &intValue );
    
    // double operators
    Number operator+( const double &doubleValue );

    Number operator-( const double &doubleValue );

    Number operator*( const double &doubleValue );

    Number operator/( const double &doubleValue );

    Number &operator+=( const double &doubleValue );

    Number &operator-=( const double &doubleValue );

    Number &operator*=( const double &doubleValue );

    Number &operator/=( const double &doubleValue );
    
    
    float operator=( const float &floatValue );

    double operator=( const double &doubleValue );

    operator float() const;

private:
    static constexpr NumberValue EPSZILON = 0.0025f;
};


#endif //CYLINDERS_NUMBER_H
