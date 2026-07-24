#pragma once
#include "ITestRunner.h"
#include "SComplex.h"
#include <iostream>

/**
 * @class sComplexTester
 * @brief Implements ITestRunner to run SComplex tests.
 */
class sComplexTester : public ITestRunner {
public:
    void RunAllTests() override;

private:
    void TestComplex();
};
