/*
 * File: sVectorTester.h
 * Author: Soumyajit C
 * Description: Declaration of the vector-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
#include "ITestRunner.h"
#include "SVector.h"
#include "SVectorT.h"
#include <iostream>
#include <string>

/**
 * @class sVectorTester
 * @brief Implements ITestRunner to run vector tests (SVector, SVectorT).
 */
class sVectorTester : public ITestRunner {
public:
    /**
     * @brief Executes all vector-related tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests the behavior of the SVector container.
     */
    void TestVector();

    /**
     * @brief Tests the behavior of the templated SVectorT container.
     */
    void TestVectorT();
};
