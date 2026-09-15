// SComplex.h
#pragma once
#include "SMathLib.h"
#include <iostream>
#include <cmath>


class SMATHLIB_API SComplex 
{
private:
    double m_dRealPart;
    double m_dImagPart;

public:
    // Constructors & Destructor
    SComplex();
    SComplex(double r, double i);
    SComplex(const SComplex& c);
    ~SComplex();

    // Data Accessors
    void set_data(double r, double i);
    void set_data(const SComplex& cx);
    void get_data(double& r, double& i) const;
    double get_real() const;
    double get_imag() const;
    void empty();

    // Math Methods (ensure all parameters are const SComplex&)
    void add_data(const SComplex& cx);
    void sub_data(const SComplex& cx);
    void mul_data(const SComplex& cx);
    void div_data(const SComplex& cx);

    double get_mod() const;
    double get_arg() const;
    void display() const;

    // Assignment & Compound Operators
    SComplex& operator=(const SComplex& s);
    SComplex& operator+=(const SComplex& s);
    SComplex& operator-=(const SComplex& s);

    // Arithmetic Operators
    SComplex operator+(const SComplex& s) const;
    SComplex operator-(const SComplex& s) const;
    SComplex operator*(const SComplex& s) const;
    SComplex operator/(const SComplex& s) const;

    // Increment / Decrement
    SComplex& operator++();       // Pre-increment
    SComplex& operator--();       // Pre-decrement
    SComplex operator++(int);     // Post-increment
    SComplex operator--(int);     // Post-decrement

    // Friend Operators with double
    friend SMATHLIB_API SComplex operator+(const SComplex& s, double f);
    friend SMATHLIB_API SComplex operator+(double f, const SComplex& s);
    friend SMATHLIB_API SComplex operator-(const SComplex& s, double f);
    friend SMATHLIB_API SComplex operator-(double f, const SComplex& s);
    friend SMATHLIB_API SComplex operator*(const SComplex& s, double f);
    friend SMATHLIB_API SComplex operator*(double f, const SComplex& s);
    friend SMATHLIB_API SComplex operator/(const SComplex& s, double f);
    friend SMATHLIB_API SComplex operator/(double f, const SComplex& s);

    friend SMATHLIB_API std::ostream& operator<<(std::ostream& os, const SComplex& c);
};

