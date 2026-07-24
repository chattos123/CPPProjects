#pragma once

class ITestRunner {
public:
    virtual ~ITestRunner() = default;

    // This must match exactly in name, return type, and parameters
    virtual void RunAllTests() = 0;
};
