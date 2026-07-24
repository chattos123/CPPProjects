#include "sCalcTester.h"

void sCalcTester::TestCalculator() {
    std::cout << "\n*** Calculator Test start ***\n";

    SCalculator calc;
    double a = 10.0, b = 5.0;

    std::cout << "Add: " << calc.add(a, b) << "\n";
    std::cout << "Subtract: " << calc.subtract(a, b) << "\n";
    std::cout << "Multiply: " << calc.multiply(a, b) << "\n";
    std::cout << "Divide: " << calc.divide(a, b) << "\n";
    std::cout << "Modulo: " << calc.mod(a, b) << "\n";

    std::cout << "*** Calculator Test end ***\n\n";
}

void sCalcTester::RunAllTests() {
    std::cout << "Running SCalculator tests...\n";
    TestCalculator();
}
