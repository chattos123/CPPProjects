/*
 * File: sQueueTester.h
 * Author: Soumyajit C
 * Description: Declaration of the queue-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
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
    /**
     * @brief Executes all queue-related tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests the behavior of the SQueue container.
     */
    void TestQueue();

    /**
     * @brief Tests the behavior of the templated SQueueT container.
     */
    void TestQueueT();
};
