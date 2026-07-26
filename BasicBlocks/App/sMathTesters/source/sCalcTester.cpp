/**
 * @file sCalcTester.cpp
 * @brief Implementation of the test runner for the SCalculator component.
 * @author Soumyajit C
 * @date 2026
 */

#include "sCalcTester.h"

/**
 * @class sCalcTester
 * @brief Test runner class responsible for verifying arithmetic operations and functionality of SCalculator.
 */

/**
 * @brief Executes test scenarios for SCalculator arithmetic operations.
 *
 * Performs functional tests on addition, subtraction, multiplication, division, and modulo operations 
 * using sample floating-point values.
 *
 * @param None
 * @return void
 * @remark Evaluates calculator operations directly and prints formatted results to std::cout.
 */
void sCalcTester::TestCalculator() 
{
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

/**
 * @brief Invokes all test routines registered under the SCalculator test suite.
 *
 * Implements the ITestRunner interface entry point by sequentially running TestCalculator().
 *
 * @param None
 * @return void
 * @remark Entry point called by external test drivers or main test runners.
 */
void sCalcTester::RunAllTests() 
{
    std::cout << "Running SCalculator tests...\n";
    TestCalculator();
}