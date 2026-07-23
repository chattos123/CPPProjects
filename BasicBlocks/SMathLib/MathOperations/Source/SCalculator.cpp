#include "SCalculator.h"
#include <cmath>
#include <stdexcept>


double SCalculator::add(double a, double b) { return a + b; }
double SCalculator::subtract(double a, double b) { return a - b; }
double SCalculator::multiply(double a, double b) { return a * b; }
double SCalculator::divide(double a, double b) {
    if (b == 0.0) throw std::runtime_error("Division by zero");
    return a / b;
}
double SCalculator::mod(double a, double b) {
    if (b == 0.0) throw std::runtime_error("Modulo by zero");
    return std::fmod(a, b);
}
