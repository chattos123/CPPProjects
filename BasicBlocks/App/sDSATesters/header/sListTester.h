#pragma once
#include "ITestRunner.h"
#include "SList.h"
#include "SListT.h"
#include <iostream>
#include <string>

/**
 * @class sListTester
 * @brief Implements ITestRunner to run list tests (SList, SListT).
 */
class sListTester : public ITestRunner {
public:
    /** @brief Runs all list tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    void TestList();
    void TestListT();
};
