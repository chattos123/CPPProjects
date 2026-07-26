/*
 * File: sHashTester.h
 * Author: Soumyajit C
 * Description: Declaration of the hash-related tester class used by the application.
 */

#pragma once
#include "ExportMacro.h"
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
    /**
     * @brief Executes all hash and dictionary tests.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Tests std::unordered_map integration with SHashMap.
     */
    void TestHashMapStd();

    /**
     * @brief Tests custom hashing with SString keys.
     */
    void TestHashMapCustomHash();

    /**
     * @brief Tests collision handling in the hash map.
     */
    void TestHashMapCollision();

    /**
     * @brief Tests the SMapDictionary behavior.
     */
    void TestSMapDictionary();
};
