/**
 * @file sMathTester.cpp
 * @brief Implementation of the master test runner for mathematical components (SCalculator, SComplex).
 * @author Soumyajit C
 * @date 2026
 * 
 * @note Design Pattern Usage:
 *  - Composite Pattern: Implements ITestRunner while managing child ITestRunner instances,
 *    allowing uniform execution of individual leaf runners and aggregated test suites.
 *  - Factory Method / Builder Assembly: Encapsulates concrete instantiation of child runners inside Setup().
 */

#include "sMathTester.h"

/**
 * @class sMathTester
 * @brief Master test runner implementation aggregating math-related module test suites.
 */

/**
 * @brief Initializes and registers individual math test runners into the internal collection.
 *
 * Allocates and pushes instances of sCalcTester and sComplexTester into the polymorphic 
 * testers vector.
 *
 * @param None
 * @return void
 * @remark Internal helper invoked automatically prior to executing test runs. Outputs registration count to std::cout.
 */
void sMathTester::Setup() 
{
    std::cout << "\nSetting up Math test suite...\n";
    testers.emplace_back(std::make_unique<sCalcTester>());
    testers.emplace_back(std::make_unique<sComplexTester>());

    std::cout << "Setup complete. " << testers.size() << " testers registered.\n";
}

/**
 * @brief Executes all registered math module unit tests sequentially.
 *
 * Invokes Setup() to populate the test runners collection and iterates over each 
 * child tester, delegating execution to their respective RunAllTests() methods.
 *
 * @param None
 * @return void
 * @remark Entry point for driving the entire math test collection.
 */
void sMathTester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running Math tests...\n";
    std::cout << "==============================\n";

    Setup();

    for (auto& tester : testers) {
        tester->RunAllTests();
    }

    std::cout << "\n==============================\n";
    std::cout << "All Math tests completed successfully.\n";
    std::cout << "==============================\n";
}