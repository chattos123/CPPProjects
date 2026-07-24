#pragma once
#include "ITestRunner.h"
#include "SStack.h"
#include "SStackT.h"
#include "SListStackT.h"
#include <iostream>
#include <string>

/**
 * @class sStackTester
 * @brief Implements ITestRunner to run stack tests (SStack, SStackT, SListStackT).
 */
class sStackTester : public ITestRunner {
public:
    /** @brief Runs all stack tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    void TestStack();
    void TestStackT();
    void TestListStack();
};
