#pragma once
#include "ITestRunner.h"
#include "sCalcTester.h"
#include "sComplexTester.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @class sMathTester
 * @brief Orchestrates math-related testers (SCalculator, SComplex).
 */
class sMathTester : public ITestRunner {
public:
    void RunAllTests() override;

private:
    std::vector<std::unique_ptr<ITestRunner>> testers;
    void Setup();
};
