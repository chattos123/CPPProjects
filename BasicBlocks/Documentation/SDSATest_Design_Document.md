# 🧩 sDSATester — Design Document

## 📘 Overview
`sDSATester` is the **master test orchestrator** for the DSA (Data Structures and Algorithms) library.  
It implements the `ITestRunner` interface and coordinates execution of all individual tester classes, ensuring a unified and extensible testing workflow.

---

## 🧱 Class Responsibilities

| Responsibility | Description |
|----------------|--------------|
| **Implements `ITestRunner`** | Provides a single entry point for running all DSA tests. |
| **Maintains a list of testers** | Holds instances of all component testers (`sHashTester`, `sStackTester`, etc.). |
| **Setup phase** | Dynamically registers all available testers. |
| **Execution phase** | Sequentially invokes `RunAllTests()` on each registered tester. |
| **Reporting** | Displays structured console output with clear start/end markers. |

---

## 🧩 Class Definition

### 📂 `sDSATester.h`

```cpp
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
class sDSATester : public ITestRunner {
public:
    /** @brief Runs all DSA tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    std::vector<std::unique_ptr<ITestRunner>> testers;

    /** @brief Initializes the test suite with all available testers. */
    void Setup();
};
