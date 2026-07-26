/**
 * @file sDSATester.h
 * @brief Master test suite header for orchestrating Data Structures & Algorithms (DSA) component tests.
 * @author Soumyajit C
 * @date 2026
 * 
 * @note Design Pattern Usage:
 *  - Composite Pattern: Implements ITestRunner while maintaining a collection of 
 *    child ITestRunner instances (leaf runners), allowing single modules and 
 *    aggregated suites to be treated uniformly via RunAllTests().
 *  - Factory Method / Helper Assembly: Encapsulates concrete component instantiation 
 *    and registration inside Setup().
 */

#pragma once

#include "ExportMacro.h"
#include "ITestRunner.h"
#include "sHashTester.h"
#include "sStackTester.h"
#include "sListTester.h"
#include "sVectorTester.h"
#include "sQueueTester.h"
#include "sTuplePairTester.h"
#include "sStringTester.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @class sDSATester
 * @brief Master orchestrator class that aggregates and executes individual DSA component test runners.
 * 
 * Implements ITestRunner to manage the lifecycle and execution sequence of various data structure 
 * unit tests (Hash Table, Stack, Linked List, Vector, Queue, Tuple/Pair, and String).
 */

class sDSATester : public ITestRunner 
{
public:
    /**
     * @brief Executes all registered DSA module test suites.
     *
     * Overrides the ITestRunner interface method to initialize all sub-testers and 
     * trigger their respective test routines sequentially.
     *
     * @param None
     * @return void
     * @remark Ensures Setup() is called prior to executing tests to populate the runner collection.
     */
    void RunAllTests() override;

private:
    /// Collection of polymorphic test runners held via smart pointers.
    std::vector<std::unique_ptr<ITestRunner>> testers;

    /**
     * @brief Instantiates and registers individual module testers into the internal execution list.
     *
     * Allocates memory for specific data structure testers (e.g., sHashTester, sStackTester) 
     * and pushes them into the testers collection.
     *
     * @param None
     * @return void
     * @remark Internal initialization helper invoked automatically prior to test execution.
     */
    void Setup();
};