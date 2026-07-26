/**
 * @file sDSATester.cpp
 * @brief Implementation of the master test runner for all Data Structures & Algorithms (DSA) components.
 * @author Soumyajit C
 * @date 2026
 * 
 * @note Design Pattern Usage:
 *  - Composite Pattern: Implements ITestRunner while managing child ITestRunner instances,
 *    allowing uniform execution of individual leaf runners and aggregated test suites.
 *  - Factory Method / Builder Assembly: Encapsulates concrete instantiation of child runners inside Setup().
 */

#include "sDSATester.h"

/**
 * @class sDSATester
 * @brief Master test runner implementation aggregating individual DSA module test suites.
 */

/**
 * @brief Initializes and registers individual DSA test runners into the internal collection.
 *
 * Allocates and pushes instances of sHashTester, sStackTester, sListTester, 
 * sVectorTester, sQueueTester, sTuplePairTester, and sStringTester into the polymorphic 
 * testers vector.
 *
 * @param None
 * @return void
 * @remark Internal helper called prior to executing test runs. Outputs progress to std::cout.
 */
void sDSATester::Setup() {
    std::cout << "\nSetting up DSA test suite...\n";

    testers.emplace_back(std::make_unique<sHashTester>());
    testers.emplace_back(std::make_unique<sStackTester>());
    testers.emplace_back(std::make_unique<sListTester>());
    testers.emplace_back(std::make_unique<sVectorTester>());
    testers.emplace_back(std::make_unique<sQueueTester>());
    testers.emplace_back(std::make_unique<sTuplePairTester>());
    testers.emplace_back(std::make_unique<sStringTester>());

    std::cout << "Setup complete. " << testers.size() << " testers registered.\n";
}

/**
 * @brief Executes all registered DSA module unit tests sequentially.
 *
 * Invokes Setup() to populate the test runners collection and iterates over each 
 * child tester, delegating execution to their respective RunAllTests() methods.
 *
 * @param None
 * @return void
 * @remark Entry point for driving the entire DSA test collection.
 */
void sDSATester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running all DSA tests...\n";
    std::cout << "==============================\n";

    Setup();

    for (auto& tester : testers) {
        tester->RunAllTests();
    }

    std::cout << "\n==============================\n";
    std::cout << "All DSA tests completed successfully.\n";
    std::cout << "==============================\n";
}