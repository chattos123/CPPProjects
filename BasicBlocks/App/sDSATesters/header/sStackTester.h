/*
 * File: sStackTester.h
 * Author: Soumyajit C
 * Description: Declaration of the stack-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
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
    /**
     * @brief Executes all stack-related tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests the behavior of the SStack container.
     */
    void TestStack();

    /**
     * @brief Tests the behavior of the templated SStackT container.
     */
    void TestStackT();

    /**
     * @brief Tests the behavior of the SListStackT container.
     */
    void TestListStack();
};
