/**
 * @file sComplexTester.h
 * @brief Header definition for the SComplex test runner module.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ITestRunner.h"
#include "SComplex.h"
#include <iostream>

/**
 * @class sComplexTester
 * @brief Test runner implementation that executes test suites for the SComplex class.
 * 
 * Inherits from the ITestRunner interface to provide a unified framework for executing 
 * unit tests targeting complex number operations, representations, and overloads.
 */
class sComplexTester : public ITestRunner {
public:
    /**
     * @brief Executes all registered complex number unit tests sequentially.
     *
     * Overrides the ITestRunner interface method to invoke the full battery of tests 
     * designed for the SComplex data structure.
     *
     * @param None
     * @return void
     * @remark Serves as the primary public entry point for running SComplex test routines.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Internal helper function to run specific functional tests on SComplex instances.
     *
     * Tests basic instantiation, arithmetic operator overloads (+, -, *, /), equality checks, 
     * polar/Cartesian conversions, and stream insertion/extraction operations.
     *
     * @param None
     * @return void
     * @remark Outputs status logs and assertion details directly to standard output.
     */
    void TestComplex();
};