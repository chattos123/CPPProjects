#pragma once
#include "ITestRunner.h"
#include "SQueue.h"
#include "SQueueT.h"
#include <iostream>
#include <string>

/**
 * @class sQueueTester
 * @brief Implements ITestRunner to run queue tests (SQueue, SQueueT).
 */
class sQueueTester : public ITestRunner {
public:
    /** @brief Runs all queue tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    void TestQueue();
    void TestQueueT();
};
