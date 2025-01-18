#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cmath>

#include "util.hpp"

class Rational {
    int _num; // always positive
    int _den; // always positive
    int _sign; // +1 or -1
public:
    Rational(int num = 0, int den = 1) : _num(num), _den(den), _sign(1) {
        reduce();
    }
    int num() {
        return _num;
    }
    int den() {
        return _den;
    }
    int sign() {
        return _sign;
    }
    void reduce() {
        if (_num * _den < 0) _sign *= -1;
        _num = std::abs(_num); _den = std::abs(_den);
        int div = gcf(_num, _den);
        _num /= div;
        _den /= div;
    }
    double to_double() {
        return double(_sign) * _num / _den;
    }
};

Rational operator+(Rational a, Rational b) {
    int lcd = lcm(a.den(), b.den());
    return Rational(a.sign() * a.num() * (lcd / a.den()) + b.sign() * b.num() * (lcd / b.den()), lcd);
}
Rational operator-(Rational a, Rational b) {
    int lcd = lcm(a.den(), b.den());
    return Rational(a.sign() * a.num() * (lcd / a.den()) - b.sign() * b.num() * (lcd / b.den()), lcd);
}
Rational operator*(Rational a, Rational b) {
    return Rational(a.sign() * a.num() * b.sign() * b.num(), a.den() * b.den());
}
Rational operator/(Rational a, Rational b) {
    return Rational(a.sign() * a.num() * b.sign() * b.den(), a.den() * b.num());
}

bool operator==(Rational a, Rational b) {
    return a.sign() == b.sign() && a.num() == b.num() && a.den() == b.den();
}

bool operator!=(Rational a, Rational b) {
    return a.sign() != b.sign() || a.num() != b.num() || a.den() != b.den();
}

#endif // RATIONAL_HPP