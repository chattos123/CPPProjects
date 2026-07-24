#pragma once
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
    /** @brief Runs all SPair/STuple tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    void TestSPair();
    void TestTuple();
};