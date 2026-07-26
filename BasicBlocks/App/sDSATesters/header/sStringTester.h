/*
 * File: sStringTester.h
 * Author: Soumyajit C
 * Description: Declaration of the string-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
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
    /**
     * @brief Executes all SString-related tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests string construction and initialization.
     */
    void TestConstruction();

    /**
     * @brief Tests assignment operations for SString.
     */
    void TestAssignment();

    /**
     * @brief Tests string concatenation behavior.
     */
    void TestConcatenation();

    /**
     * @brief Tests append operations for SString.
     */
    void TestAppend();

    /**
     * @brief Tests case conversion functions.
     */
    void TestCaseConversions();

    /**
     * @brief Tests reverse operations.
     */
    void TestReverse();

    /**
     * @brief Tests substring extraction behavior.
     */
    void TestSubstring();

    /**
     * @brief Tests indexing and access operations.
     */
    void TestIndexing();

    /**
     * @brief Tests comparison operators and methods.
     */
    void TestComparison();

    /**
     * @brief Tests clearing the string contents.
     */
    void TestClear();

    /**
     * @brief Tests conversion helpers for the string type.
     */
    void TestConversions();

    /**
     * @brief Tests input handling and parsing behavior.
     */
    void TestInput();

    /**
     * @brief Tests tokenization behavior.
     */
    void TestTokenize();

    /**
     * @brief Tests iterator support for SString.
     */
    void TestIterator();

    /**
     * @brief Tests support for Unicode text handling.
     */
    void TestUnicodeText();

    /**
     * @brief Tests the cast operator behavior.
     */
    void TestCastOpearator();
};
