#pragma once
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
    /** @brief Runs all vector tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    void TestVector();
    void TestVectorT();
};
