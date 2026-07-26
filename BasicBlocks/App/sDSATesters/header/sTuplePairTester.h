/*
 * File: sTuplePairTester.h
 * Author: Soumyajit C
 * Description: Declaration of the tuple and pair tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
#include "ITestRunner.h"
#include "SPair.h"
#include "STuple.h"
#include "STupleGet.h"
#include <iostream>
#include <string>

/**
 * @class sTuplePairTester
 * @brief Implements ITestRunner to run SPair and STuple tests.
 */
class sTuplePairTester : public ITestRunner {
public:
    /**
     * @brief Executes all SPair and STuple-related tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests the behavior of the SPair container.
     */
    void TestSPair();

    /**
     * @brief Tests the behavior of the STuple container.
     */
    void TestTuple();
};