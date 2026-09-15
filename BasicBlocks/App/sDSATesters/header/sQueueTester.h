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
#include "SCircularQ.h"
#include "SCircularQT.h"
#include "SListQT.h"
#include "SListCircularQT.h"
#include "SAssendingPriorityQT.h"
#include "SDecendingPriorityQT.h"
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
    /**
     * @brief Tests the behavior of the templated SCircularQ container.
     */
    void TestCircularQ();  
    /**
     * @brief Tests the behavior of the templated SCircularQT container.
     */
    void TestCircularQT(); 

    /**
     * @brief Tests iterator traversal for SCircularQT.
     */
    void TestCircularQTIterators(); 
     /**
     * @brief //Tests exception handling (overflow/underflow) for SCircularQT.
     */
    void TestCircularQTNegative();  

    private:
    /**
     * @brief Tests the behavior of the SListQT container.
     */
    void TestSListQT();

    /**
     * @brief Tests the behavior of the SListCircularQT container.
     */
    void TestSListCircularQT();

    /**
     * @brief Tests exception handling (underflow/invalid ops) for SListCircularQT.
     */
    void TestSListCircularQTNegative();
      /**
     * @brief Tests the behavior of the ascending priority queue (SAssendingPriorityQT).
     */
    void TestSAssendingPriorityQT();
    /**
     * @brief Tests exception handling (underflow/empty ops) for SAssendingPriorityQT.
     */
    void TestSAssendingPriorityQTNegative();
    /**
     * @brief Performance benchmark for SAssendingPriorityQT under bulk operations.
     */
    void TestSAssendingPriorityQTPerformance();
    /**
     * @brief Tests the behavior of the descending priority queue (SDecendingPriorityQT).
     */
    void TestSDecendingPriorityQT();
    /**
     * @brief Tests exception handling (underflow/empty ops) for SDecendingPriorityQT.
     */
    void TestSDecendingPriorityQTNegative();

    /**
     * @brief Performance benchmark for SDecendingPriorityQT under bulk operations.
     */
    void TestSDecendingPriorityQTPerformance();



};
