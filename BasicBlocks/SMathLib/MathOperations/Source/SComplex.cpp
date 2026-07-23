// SComplex.cpp
// ...existing code...
#include "SComplex.h"
#include <iostream>
#include <cmath>   // for std::fabs
#include <stdexcept> // <--- added
// ...existing code...  // for std::fabs

// Constructors
SComplex::SComplex() : m_dRealPart(0.0), m_dImagPart(0.0) {}
SComplex::SComplex(double r, double i) : m_dRealPart(r), m_dImagPart(i) {}
SComplex::SComplex(const SComplex& c) : m_dRealPart(c.m_dRealPart), m_dImagPart(c.m_dImagPart) {}

// Destructor
SComplex::~SComplex() {}

// Members
void SComplex::set_data(double r, double i) { m_dRealPart = r; m_dImagPart = i; }
void SComplex::set_data(const SComplex& cx) { m_dRealPart = cx.m_dRealPart; m_dImagPart = cx.m_dImagPart; }
void SComplex::get_data(double& r, double& i) const { r = m_dRealPart; i = m_dImagPart; }
double SComplex::get_real() const { return m_dRealPart; }
double SComplex::get_imag() const { return m_dImagPart; }
void SComplex::empty() { m_dRealPart = 0.0; m_dImagPart = 0.0; }

void SComplex::add_data(const SComplex& cx) { m_dRealPart += cx.m_dRealPart; m_dImagPart += cx.m_dImagPart; }
void SComplex::sub_data(const SComplex& cx) { m_dRealPart -= cx.m_dRealPart; m_dImagPart -= cx.m_dImagPart; }

void SComplex::mul_data(const SComplex& cx) {
    double temp_rl = m_dRealPart * cx.m_dRealPart - m_dImagPart * cx.m_dImagPart;
    double temp_ig = m_dRealPart * cx.m_dImagPart + m_dImagPart * cx.m_dRealPart;
    m_dRealPart = temp_rl;
    m_dImagPart = temp_ig;
}

void SComplex::div_data(const SComplex& cx) {
    double mod = cx.m_dRealPart * cx.m_dRealPart + cx.m_dImagPart * cx.m_dImagPart;
    if (mod == 0.0) {
        empty();
        throw std::runtime_error("Divide by zero error");
    }
    double temp_rl = (m_dRealPart * cx.m_dRealPart + m_dImagPart * cx.m_dImagPart) / mod;
    double temp_ig = (m_dImagPart * cx.m_dRealPart - m_dRealPart * cx.m_dImagPart) / mod;
    m_dRealPart = temp_rl;
    m_dImagPart = temp_ig;
}

double SComplex::get_mod() const { return std::sqrt(m_dRealPart * m_dRealPart + m_dImagPart * m_dImagPart); }
double SComplex::get_arg() const { return std::atan2(m_dImagPart, m_dRealPart); }

void SComplex::display() const 
{
    std::cout << "R:"<< this->get_real()<<", I:" <<this->get_imag()<< std::endl;
}

// Operator overloading
SComplex SComplex::operator+(const SComplex& s) const 
{
    return SComplex(m_dRealPart + s.m_dRealPart, m_dImagPart + s.m_dImagPart);
}

SComplex SComplex::operator-(const SComplex& s) const 
{
    return SComplex(m_dRealPart - s.m_dRealPart, m_dImagPart - s.m_dImagPart);
}

SComplex SComplex::operator*(const SComplex& s) const 
{
    return SComplex(m_dRealPart * s.m_dRealPart - m_dImagPart * s.m_dImagPart,
                    m_dRealPart * s.m_dImagPart + m_dImagPart * s.m_dRealPart);
}

SComplex SComplex::operator/(const SComplex& s) const 
{
    double mod = s.m_dRealPart * s.m_dRealPart + s.m_dImagPart * s.m_dImagPart;
    if (mod == 0.0) throw std::runtime_error("Divide by zero error");
    return SComplex((m_dRealPart * s.m_dRealPart + m_dImagPart * s.m_dImagPart) / mod,
                    (m_dImagPart * s.m_dRealPart - m_dRealPart * s.m_dImagPart) / mod);
}

SComplex& SComplex::operator=(const SComplex& s) {
    if (this != &s) {
        m_dRealPart = s.m_dRealPart;
        m_dImagPart = s.m_dImagPart;
    }
    return *this;
}

// Increment/Decrement
SComplex& SComplex::operator++() { ++m_dRealPart; ++m_dImagPart; return *this; }
SComplex& SComplex::operator--() { --m_dRealPart; --m_dImagPart; return *this; }
SComplex SComplex::operator++(int) { SComplex temp(*this); ++(*this); return temp; }
SComplex SComplex::operator--(int) { SComplex temp(*this); --(*this); return temp; }

// Compound assignment
SComplex& SComplex::operator+=(const SComplex& s) { m_dRealPart += s.m_dRealPart; m_dImagPart += s.m_dImagPart; return *this; }
SComplex& SComplex::operator-=(const SComplex& s) { m_dRealPart -= s.m_dRealPart; m_dImagPart -= s.m_dImagPart; return *this; }

// Friend functions
SComplex operator+(const SComplex& s, double f) { return SComplex(s.m_dRealPart + f, s.m_dImagPart + f); }

SComplex operator+(double f, const SComplex& s) { return SComplex(f + s.m_dRealPart, f + s.m_dImagPart); }

SComplex operator-(const SComplex& s, double f) { return SComplex(s.m_dRealPart - f, s.m_dImagPart - f); }

SComplex operator-(double f, const SComplex& s) { return SComplex(f - s.m_dRealPart, f - s.m_dImagPart); }

SComplex operator*(const SComplex& s, double f) { return SComplex(s.m_dRealPart * f, s.m_dImagPart * f); }

SComplex operator*(double f, const SComplex& s) { return SComplex(f * s.m_dRealPart, f * s.m_dImagPart); }

SComplex operator/(const SComplex& s, double f)
{
    if (f == 0.0) throw std::runtime_error("Divide by zero error");
    return SComplex(s.m_dRealPart / f, s.m_dImagPart / f);
}

SComplex operator/(double f, const SComplex& s) 
{
    return SComplex(f, 0) / s;
}


std::ostream& operator<<(std::ostream& os, const SComplex& c)
{
    os << c.get_real()
       << (c.get_imag() >= 0 ? " + " : " - ")
       << std::fabs(c.get_imag()) << "i";
    return os;
}


