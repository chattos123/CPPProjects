#pragma once
#include "SMathLib.h"
#include <stdexcept>

class SMATHLIB_API SCalculator 
{
public:
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    double mod(double a, double b);
};
