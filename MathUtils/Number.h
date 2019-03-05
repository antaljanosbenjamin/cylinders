//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_NUMBER_H
#define CYLINDERS_NUMBER_H

#include <cmath>

template <typename T>
struct NumberBase
{

  private:
    static constexpr T EPSZILON = 0.0025;

  public:
    T value;

    NumberBase()
        : value(T()) {}

    explicit NumberBase(const T &value)
        : value(value){};

    bool operator==(const NumberBase<T> &other) const
    {
        return (value < other.value + EPSZILON && value > other.value - EPSZILON);
    }

    bool operator!=(const NumberBase<T> &other) const
    {
        return !(*this == other);
    }

    bool operator>(const NumberBase<T> &other) const
    {
        return value >= other.value + EPSZILON;
    }

    bool operator<(const NumberBase<T> &other) const
    {
        return value <= other.value - EPSZILON;
    }

    bool operator>=(const NumberBase<T> &other) const
    {
        return !operator<(other);
    }

    bool operator<=(const NumberBase<T> &other) const
    {
        return !operator>(other);
    }

    NumberBase<T> operator+(const NumberBase<T> &other) const
    {
        return NumberBase<T>(value + other.value);
    }

    NumberBase<T> operator-(const NumberBase<T> &other) const
    {
        return NumberBase<T>(value - other.value);
    }

    NumberBase<T> operator*(const NumberBase<T> &other) const
    {
        return NumberBase<T>(value * other.value);
    }

    NumberBase<T> operator/(const NumberBase<T> &other) const
    {
        return NumberBase<T>(value / other.value);
    }

    NumberBase<T> &operator+=(const NumberBase<T> &other)
    {
        value += other.value;
        return (*this);
    }

    NumberBase<T> &operator-=(const NumberBase<T> &other)
    {
        value -= other.value;
        return (*this);
    }

    NumberBase<T> &operator*=(const NumberBase<T> &other)
    {
        value *= other.value;
        return (*this);
    }

    NumberBase<T> &operator/=(const NumberBase<T> &other)
    {
        value /= other.value;
        return (*this);
    }

    NumberBase<T> operator-() const
    {
        return NumberBase<T>(-value);
    }

    // double operators
    bool operator==(const T &tValue) const
    {
        return *this == NumberBase<T>(tValue);
    }

    bool operator!=(const T &tValue) const
    {
        return *this != NumberBase<T>(tValue);
    }

    bool operator>(const T &tValue) const
    {
        return *this > NumberBase<T>(tValue);
    }

    bool operator<(const T &tValue) const
    {
        return *this < NumberBase<T>(tValue);
    }

    bool operator>=(const T &tValue) const
    {
        return *this >= NumberBase<T>(tValue);
    }

    bool operator<=(const T &tValue) const
    {
        return *this <= NumberBase<T>(tValue);
    }

    NumberBase<T> operator+(const T &tValue) const
    {
        return *this + NumberBase<T>(tValue);
    }

    NumberBase<T> operator-(const T &tValue) const
    {
        return *this - NumberBase<T>(tValue);
    }

    NumberBase<T> operator*(const T &tValue) const
    {
        return *this * NumberBase<T>(tValue);
    }

    NumberBase<T> operator/(const T &tValue) const
    {
        return *this / NumberBase<T>(tValue);
    }

    NumberBase<T> &operator+=(const T &tValue)
    {
        return *this += NumberBase<T>(tValue);
    }

    NumberBase<T> &operator-=(const T &tValue)
    {
        return *this -= NumberBase<T>(tValue);
    }

    NumberBase<T> &operator*=(const T &tValue)
    {
        return *this *= NumberBase<T>(tValue);
    }

    NumberBase<T> &operator/=(const T &tValue)
    {
        return *this /= NumberBase<T>(tValue);
    }

    double operator=(const T &tValue)
    {
        *this = NumberBase<T>(tValue);
        return tValue;
    }

    static NumberBase<T> pow(const NumberBase<T> &base, const NumberBase<T> &exponent)
    {
        return NumberBase<T>(std::pow(base.value, exponent.value));
    }

    static NumberBase<T> pow(const NumberBase<T> &base, const double exponent)
    {
        return NumberBase<T>(std::pow(base.value, exponent));
    }

    static NumberBase<T> sqrt(const NumberBase<T> &x)
    {
        return NumberBase<T>(std::sqrt(x.value));
    }

    static NumberBase<T> abs(const NumberBase<T> &x)
    {
        return NumberBase<T>(fabs(x.value));
    }

    static NumberBase<T> sin(const NumberBase<T> &x)
    {
        return NumberBase<T>(std::sin(x.value));
    }

    static NumberBase<T> cos(const NumberBase<T> &x)
    {
        return NumberBase<T>(std::cos(x.value));
    }
};

template <typename T, typename U>
NumberBase<T> operator+(const U &lhs, const NumberBase<T> &rhs)
{
    return NumberBase<T>(lhs) + rhs;
}

template <typename T, typename U>
NumberBase<T> operator-(const U &lhs, const NumberBase<T> &rhs)
{
    return NumberBase<T>(lhs) - rhs;
}

template <typename T, typename U>
NumberBase<T> operator*(const U &lhs, const NumberBase<T> &rhs)
{
    return NumberBase<T>(lhs) * rhs;
}

template <typename T, typename U>
NumberBase<T> operator/(const U &lhs, const NumberBase<T> &rhs)
{
    return NumberBase<T>(lhs) / rhs;
}

typedef NumberBase<float> Number;

#define nsqrt(X) Number::sqrt(X)
#define npow(BASE, EXPONENT) Number::pow(BASE, EXPONENT)
#define nabs(X) Number::abs(X)
#define ncos(X) Number::cos(X)
#define nsin(X) Number::sin(X)

#endif //CYLINDERS_NUMBER_H
