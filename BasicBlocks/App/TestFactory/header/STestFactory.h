/**
 * @file STestFactory.h
 * @brief Factory interface for instantiating test runners based on execution context.
 * @author Soumyajit C
 * @date 2026
 * 
 * @note Design Pattern Usage:
 *  - Factory Method / Static Factory: Encapsulates the instantiation logic for 
 *    various test runner aggregates (Math, DSA, or All) based on the supplied TestContext.
 */

#pragma once

#include "ITestRunner.h"
#include "sMathTester.h"
#include "sDSATester.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @enum TestContext
 * @brief Categorizes the available test suite execution scopes.
 */
enum class TestContext 
{
    Math,  ///< Run only mathematical component tests (SCalculator, SComplex).
    DSA,   ///< Run only Data Structures & Algorithms component tests.
    All    ///< Run all available test suites across all domains.
};

/**
 * @class STestFactory
 * @brief Static factory class responsible for constructing test runner collections.
 * 
 * Abstractly handles test runner creation so clients do not need to know concrete 
 * test runner types or instantiation details.
 */
class STestFactory 
{
public:
    /**
     * @brief Instantiates and returns a collection of test runners matching the target context.
     *
     * Constructs dynamic instances of sMathTester, sDSATester, or both based on the enum provided.
     *
     * @param[in] ctx The selected test execution scope (TestContext::Math, TestContext::DSA, or TestContext::All).
     * @return std::vector<std::unique_ptr<ITestRunner>> Vector containing unique pointers to constructed test runners.
     * @remark Ownership of the returned test runners is transferred entirely to the caller via std::unique_ptr.
     */
    static std::vector<std::unique_ptr<ITestRunner>> CreateTesters(TestContext ctx);
};