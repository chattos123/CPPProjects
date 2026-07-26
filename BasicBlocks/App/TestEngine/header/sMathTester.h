/**
 * @file sMathTester.h
 * @brief Header definition for the mathematical components test suite orchestrator.
 * @author Soumyajit C
 * @date 2026
 * 
 * @note Design Pattern Usage:
 *  - Composite Pattern: Implements ITestRunner while maintaining a collection of 
 *    child ITestRunner instances (sCalcTester, sComplexTester), allowing single modules 
 *    and aggregated math suites to be treated uniformly via RunAllTests().
 *  - Factory Method / Helper Assembly: Encapsulates concrete component instantiation 
 *    and registration inside Setup().
 */

#pragma once

#include "ExportMacro.h"
#include "ITestRunner.h"
#include "sCalcTester.h"
#include "sComplexTester.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @class sMathTester
 * @brief Orchestrates math-related test suites (SCalculator, SComplex).
 * 
 * Implements the ITestRunner interface to aggregate and execute unit tests 
 * targeting mathematical classes and utilities.
 */
class sMathTester : public ITestRunner 
{
public:
    /**
     * @brief Executes all registered math-related test suites sequentially.
     *
     * Overrides the ITestRunner interface method to initialize sub-testers via Setup() 
     * and trigger their respective test execution sequences.
     *
     * @param None
     * @return void
     * @remark Ensures Setup() is invoked internally prior to running tests.
     */
    void RunAllTests() override;

private:
    /// Collection of polymorphic math test runners held via smart pointers.
    std::vector<std::unique_ptr<ITestRunner>> testers;

    /**
     * @brief Instantiates and registers individual math module testers into the execution list.
     *
     * Allocates memory for specific math testers (e.g., sCalcTester, sComplexTester) 
     * and pushes them into the testers collection.
     *
     * @param None
     * @return void
     * @remark Internal initialization helper invoked automatically during test execution.
     */
    void Setup();
};