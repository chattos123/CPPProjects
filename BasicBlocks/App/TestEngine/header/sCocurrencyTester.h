/**
 * @file sCocurrencyTester.h
 * @brief Declaration of the master test runner for all Concurrency components.
 * @author Soumyajit C
 * @date 2026
 *
 * @note Design Pattern Usage:
 *  - Composite Pattern: Implements ITestRunner while managing child ITestRunner instances
 *    (such as sTCPSocketTester and future thread/IPC testers) uniformly.
 */

#pragma once

#include "ITestRunner.h"
#include "sTCPSocketTester.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @class sCocurrencyTester
 * @brief Master test runner aggregating individual Concurrency module test suites.
 */
class sCocurrencyTester : public ITestRunner
{
public:
    /**
     * @brief Constructs the master concurrency test runner.
     * @param config_path Path to the configuration file passed to config-driven testers (defaults to "config.ini").
     */
    explicit sCocurrencyTester(std::string config_path = "Concurrency/Socket/config.ini");

    /**
     * @brief Virtual destructor.
     */
    ~sCocurrencyTester() override = default;

    /**
     * @brief Executes all registered Concurrency module tests sequentially.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Initializes and registers individual Concurrency test runners into the internal collection.
     */
    void Setup();

    std::string config_path_;                          ///< Configuration file path for socket/process testers.
    std::vector<std::unique_ptr<ITestRunner>> testers; ///< Polymorphic collection of child concurrency testers.
};