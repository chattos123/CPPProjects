// SComplex.h
#pragma once
#include <iostream>
#include <cmath>

#ifdef MATHLIB_EXPORTS
#define SMATHLIB_API __declspec(dllexport)
#else
#define SMATHLIB_API __declspec(dllimport)
#endif

class SMATHLIB_API SComplex
{
    private:
    double m_dRealPart;
    double m_dImagPart;

public:
    // Constructors
    SComplex();
    SComplex(double r, double i);
    SComplex(const SComplex& c);

    // Destructor
    ~SComplex();

    // Members
    void set_data(double r, double i);
    void set_data(const SComplex& cx);
    void get_data(double& r, double& i) const;
    double get_real() const;
    double get_imag() const;
    void empty();

    void add_data(const SComplex& cx);
    void sub_data(const SComplex& cx);
    void mul_data(const SComplex& cx);
    void div_data(const SComplex& cx);

    double get_mod() const;
    double get_arg() const;

    void display() const;

    // Operator overloading
    SComplex operator+(const SComplex& s) const;
    SComplex operator-(const SComplex& s) const;
    SComplex operator*(const SComplex& s) const;
    SComplex operator/(const SComplex& s) const;

    SComplex& operator=(const SComplex& s);

    // Increment/Decrement
    SComplex& operator++();    // prefix
    SComplex& operator--();    // prefix
    SComplex operator++(int);  // postfix
    SComplex operator--(int);  // postfix

    // Compound assignment
    SComplex& operator+=(const SComplex& s);
    SComplex& operator-=(const SComplex& s);

    // Friend functions for double operations
    friend SComplex operator+(const SComplex& s, double f);
    friend SComplex operator+(double f, const SComplex& s);
    friend SComplex operator-(const SComplex& s, double f);
    friend SComplex operator-(double f, const SComplex& s);
    friend SComplex operator*(const SComplex& s, double f);
    friend SComplex operator*(double f, const SComplex& s);
    friend SComplex operator/(const SComplex& s, double f);
    friend SComplex operator/(double f, const SComplex& s);

    // Stream output
    SMATHLIB_API friend std::ostream& operator<<(std::ostream& os, const SComplex& c);
};

