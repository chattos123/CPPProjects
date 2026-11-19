/**
 * @file sCocurrencyTester.cpp
 * @brief Implementation of the master test runner for all Concurrency components.
 * @author Soumyajit C
 * @date 2026
 *
 * @note Design Pattern Usage:
 *  - Composite Pattern: Implements ITestRunner while managing child ITestRunner instances,
 *    allowing uniform execution of individual leaf runners and aggregated test suites.
 *  - Factory Method / Builder Assembly: Encapsulates concrete instantiation of child runners inside Setup().
 */

#include "sCocurrencyTester.h"

#include <utility>

/**
 * @class sCocurrencyTester
 * @brief Master test runner implementation aggregating individual Concurrency module test suites.
 */

/**
 * @brief Constructs sCocurrencyTester with a target configuration file path.
 *
 * @param config_path Path to config.ini used by config-driven concurrency testers.
 */
sCocurrencyTester::sCocurrencyTester(std::string config_path)
    : config_path_(std::move(config_path)) {}

/**
 * @brief Initializes and registers individual Concurrency test runners into the internal collection.
 *
 * Clears any previously registered runners and pushes concrete instances (starting with
 * sTCPSocketTester) into the polymorphic testers vector. Add future thread, mutex, or
 * process testers here as new leaf ITestRunner implementations are created.
 *
 * @param None
 * @return void
 * @remark Internal helper called prior to executing test runs. Outputs progress to std::cout.
 */
void sCocurrencyTester::Setup()
{
    std::cout << "\nSetting up Concurrency test suite...\n";

    testers.clear();
    testers.emplace_back(std::make_unique<sTCPSocketTester>(config_path_));
    // Future concurrency testers can be registered here:
    // testers.emplace_back(std::make_unique<sThreadPoolTester>());
    // testers.emplace_back(std::make_unique<sMutexTester>());

    std::cout << "Setup complete. " << testers.size() << " testers registered.\n";
}

/**
 * @brief Executes all registered Concurrency module unit tests sequentially.
 *
 * Invokes Setup() to populate the test runners collection and iterates over each
 * child tester, delegating execution to their respective RunAllTests() methods.
 *
 * @param None
 * @return void
 * @remark Entry point for driving the entire Concurrency test collection.
 */
void sCocurrencyTester::RunAllTests()
{
    std::cout << "\n==============================\n";
    std::cout << "Running all Concurrency tests...\n";
    std::cout << "==============================\n";

    Setup();

    for (auto &tester : testers)
    {
        tester->RunAllTests();
    }

    std::cout << "\n==============================\n";
    std::cout << "All Concurrency tests completed successfully.\n";
    std::cout << "==============================\n";
}