/*
 * File: sTreeTester.h
 * Author: Soumyajit C
 * Description: Declaration of the tree-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
#include "ITestRunner.h"
/**
 * @class sTreeTester
 * @brief Implements ITestRunner to run tree tests (SStrictBTree).
 */
class sTreeTester : public ITestRunner 
{

public:
    /**
     * @brief Executes all tree-related tests.
     */
    void RunAllTests() override;
    private:
    /**
     * @brief Tests the behavior of the SStrictBTree container.
     */     
    void TestSStrictBTree();
}