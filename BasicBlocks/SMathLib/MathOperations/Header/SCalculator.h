#pragma once
#include "SMathLib.h"
#include <stdexcept>

#ifdef MATHLIB_EXPORTS
#define SMATHLIB_API __declspec(dllexport)
#else
#define SMATHLIB_API __declspec(dllimport)
#endif

class SMATHLIB_API SCalculator {
public:
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    double mod(double a, double b);
};
