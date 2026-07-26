/**
 * @file sCalcTester.h
 * @brief Header definition for the SCalculator test runner module.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ITestRunner.h"
#include "SCalculator.h"
#include <iostream>

/**
 * @class sCalcTester
 * @brief Test runner implementation that executes test suites for the SCalculator component.
 * 
 * Inherits from the ITestRunner interface to provide a uniform test execution interface across different modules.
 */
class sCalcTester : public ITestRunner 
{
public:
    /**
     * @brief Executes all registered calculator test suites sequentially.
     *
     * Overrides the ITestRunner interface method to trigger the complete set of standard 
     * and edge-case unit tests for SCalculator.
     *
     * @param None
     * @return void
     * @remark Serves as the main external entry point for test suite invocation.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Internal helper function to run specific functional tests on SCalculator.
     *
     * Exercises various arithmetic operations, error handling scenarios (e.g., division by zero), 
     * and state validations within the calculator component.
     *
     * @param None
     * @return void
     * @remark Prints test status and assertions directly to standard console output.
     */
    void TestCalculator();
};