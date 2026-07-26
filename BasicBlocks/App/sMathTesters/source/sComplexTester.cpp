/**
 * @file sComplexTester.cpp
 * @brief Implementation of the test runner for the SComplex complex number class.
 * @author Soumyajit C
 * @date 2026
 */

#include "sComplexTester.h"

/**
 * @class sComplexTester
 * @brief Test runner class responsible for verifying mathematical operations and stream output of SComplex.
 */

/**
 * @brief Executes unit tests for the SComplex class operations.
 *
 * Exercises complex number arithmetic including addition, subtraction, multiplication, 
 * division, and stream extraction/insertion operator overloads.
 *
 * @param None
 * @return void
 * @remark Outputs complex number arithmetic evaluations directly to standard console output.
 */
void sComplexTester::TestComplex() 
{
    std::cout << "\n*** Complex Test start ***\n";

    SComplex c1(3.0, 4.0);
    SComplex c2(1.0, 2.0);

    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";

    std::cout << "c1 + c2 = " << (c1 + c2) << "\n";
    std::cout << "c1 - c2 = " << (c1 - c2) << "\n";
    std::cout << "c1 * c2 = " << (c1 * c2) << "\n";
    std::cout << "c1 / c2 = " << (c1 / c2) << "\n";

    std::cout << "*** Complex Test end ***\n\n";
}

/**
 * @brief Triggers all test suites associated with the SComplex component.
 *
 * Implements the ITestRunner interface method by initiating the sequence of complex number tests.
 *
 * @param None
 * @return void
 * @remark Called by external test frameworks or main runner loops to execute SComplex validation.
 */
void sComplexTester::RunAllTests() 
{
    std::cout << "Running SComplex tests...\n";
    TestComplex();
}