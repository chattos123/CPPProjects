#pragma once
#include "SHashMap.h"
#include "SMapDictionary.h"
#include "SString.h"
#include "ITestRunner.h"
#include <iostream>

/**
 * @brief Custom hash functor for SString.
 * Uses a simple polynomial rolling hash on wide characters.
 */
struct SStringHash 
{
    std::size_t operator()(const SString& s) const noexcept 
    {
        std::size_t h = 0;

        const int prime = 31;
        for (wchar_t c : s.ToString()) {   // iterate over std::wstring
            h = h * prime + static_cast<unsigned int>(c);
        }
        return h;
    }
};

/**
 * @class sHashTester
 * @brief Implements ITestRunner to run SHashMap tests.
 */
class sHashTester : public ITestRunner {
public:
    /** @brief Runs all tests (override from ITestRunner). */
    void RunAllTests() override;

private:
    void TestHashMapStd();
    void TestHashMapCustomHash();
    void TestHashMapCollision();
    void TestSMapDictionary();
};
