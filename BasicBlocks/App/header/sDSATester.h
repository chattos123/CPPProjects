#pragma once
#include "ITestRunner.h"
#include "sHashTester.h"
#include "sStackTester.h"
#include "sListTester.h"
#include "sVectorTester.h"
#include "sQueueTester.h"
#include "sTuplePairTester.h"
#include "sStringTester.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @class sDSATester
 * @brief Master orchestrator that runs all DSA component tests.
 */
class sDSATester : public ITestRunner 
{
public:
    /** @brief Runs all DSA tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    std::vector<std::unique_ptr<ITestRunner>> testers;

    void Setup();
};
