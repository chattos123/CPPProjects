#pragma once
#include "ITestRunner.h"
#include "sMathTester.h"
#include "sDSATester.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @enum TestContext
 * @brief Defines which test suite(s) to run.
 */
enum class TestContext {
    Math,
    DSA,
    All
};

/**
 * @class STestFactory
 * @brief Factory that provides a list of testers based on context.
 */
class STestFactory {
public:
    /**
     * @brief Creates a list of testers based on the given context.
     * @param ctx The test context (Math, DSA, All).
     * @return A vector of unique_ptr to ITestRunner.
     */
    static std::vector<std::unique_ptr<ITestRunner>> CreateTesters(TestContext ctx);
};
