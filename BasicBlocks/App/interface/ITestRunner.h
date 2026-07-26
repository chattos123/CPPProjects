/*
 * File: ITestRunner.h
 * Author: Soumyajit C
 * Description: Interface for test runners used by the application.
 */

#pragma once

class ITestRunner {
public:
    virtual ~ITestRunner() = default;

    /**
     * Executes all tests provided by the implementing test runner.
     */
    virtual void RunAllTests() = 0;
};
