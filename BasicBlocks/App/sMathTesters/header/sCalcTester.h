#pragma once
#include "ITestRunner.h"
#include "SCalculator.h"
#include <iostream>

/**
 * @class sCalcTester
 * @brief Implements ITestRunner to run SCalculator tests.
 */
class sCalcTester : public ITestRunner {
public:
    void RunAllTests() override;

private:
    void TestCalculator();
};
