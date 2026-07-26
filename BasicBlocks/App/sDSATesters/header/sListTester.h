/*
 * File: sListTester.h
 * Author: Soumyajit C
 * Description: Declaration of the list-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
#include "ITestRunner.h"
#include "SList.h"
#include "SListT.h"
#include <iostream>
#include <string>

/**
 * @class sListTester
 * @brief Implements ITestRunner to run list tests (SList, SListT).
 */
class sListTester : public ITestRunner {
public:
    /**
     * @brief Executes all list-related tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests the behavior of the SList container.
     */
    void TestList();

    /**
     * @brief Tests the behavior of the templated SListT container.
     */
    void TestListT();
};
