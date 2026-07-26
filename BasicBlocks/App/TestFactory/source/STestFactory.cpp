/**
 * @file STestFactory.cpp
 * @brief Implementation of the static factory for instantiating test runner collections.
 * @author Soumyajit C
 * @date 2026
 * 
 * @note Design Pattern Usage:
 *  - Factory Method / Static Factory Pattern: Encapsulates creation logic for polymorphic 
 *    ITestRunner instances based on the requested TestContext, decoupling callers from concrete test runner types.
 */

#include "STestFactory.h"

/**
 * @class STestFactory
 * @brief Factory class providing static creation routines for ITestRunner objects.
 */

/**
 * @brief Constructs and returns a list of test runners based on the specified context.
 *
 * Evaluates the supplied context switch and instantiates the appropriate combination 
 * of sMathTester and sDSATester instances into a collection of unique pointers.
 *
 * @param[in] ctx Enum value specifying the execution scope (TestContext::Math, TestContext::DSA, or TestContext::All).
 * @return std::vector<std::unique_ptr<ITestRunner>> Vector of managed unique pointers to the created test runners.
 * @remark Transfer of ownership occurs upon return. Prints informational logs to std::cout indicating selected context.
 */
std::vector<std::unique_ptr<ITestRunner>> STestFactory::CreateTesters(TestContext ctx) 
{
    std::vector<std::unique_ptr<ITestRunner>> testers;

    switch (ctx) 
    {
        case TestContext::Math:
        {
            std::cout << "Factory: Providing Math testers...\n";
            testers.emplace_back(std::make_unique<sMathTester>());
        }
            break;

        case TestContext::DSA:
        {
            std::cout << "Factory: Providing DSA testers...\n";
            testers.emplace_back(std::make_unique<sDSATester>());
        }
            break;

        case TestContext::All:
        {
            std::cout << "Factory: Providing ALL testers (Math + DSA)...\n";
            testers.emplace_back(std::make_unique<sMathTester>());
            testers.emplace_back(std::make_unique<sDSATester>());
        }
            break;

        default:
            std::cout << "Factory: Invalid context, no testers created.\n";
            break;
    }

    return testers;
}