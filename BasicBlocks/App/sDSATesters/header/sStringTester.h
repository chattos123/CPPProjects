#pragma once
#include "ITestRunner.h"
#include "SString.h"
#include <iostream>
#include <string>
#include <algorithm>

/**
 * @class sStringTester
 * @brief Implements ITestRunner to run SString tests.
 */
class sStringTester : public ITestRunner {
public:
    /** @brief Runs all SString tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    // SRP: each test focuses on one responsibility
    void TestConstruction();
    void TestAssignment();
    void TestConcatenation();
    void TestAppend();
    void TestCaseConversions();
    void TestReverse();
    void TestSubstring();
    void TestIndexing();
    void TestComparison();
    void TestClear();
    void TestConversions();
    void TestInput();
    void TestTokenize();
    void TestIterator();
    void TestUnicodeText();
};
