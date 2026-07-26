/*
 * File: sTuplePairTester.cpp
 * Author: Soumyajit C
 * Description: Implements the tuple and pair tester methods for the application.
 */

#include "sTuplePairTester.h"

/**
 * @brief Tests the behavior of the SPair container.
 * @remark This method validates pair creation, display output, and ordering comparisons.
 * @return void
 */
void sTuplePairTester::TestSPair() {
    std::cout << "\n*** TestSPair start ***\n";
    std::cout << "SPair iter tests start.\n";

    SPair<std::string, int> p1("Alice", 25);
    SPair<std::string, int> p2("Bob", 30);

    std::cout << p1.first << " is " << p1.second << " years old.\n";
    std::cout << p2.first << " is " << p2.second << " years old.\n";

    auto p3 = make_spair("Charlie", 35);
    std::cout << p3.first << " is " << p3.second << " years old.\n";

    if (p1 < p2) {
        std::cout << p1.first << " comes before " << p2.first << "\n";
    }

    std::cout << "SPair iter tests End.\n";
    std::cout << "*** TestSPair end ***\n";
}

/**
 * @brief Tests the behavior of the STuple container.
 * @remark This method validates tuple construction and element access using get<>().
 * @return void
 */
void sTuplePairTester::TestTuple() {
    std::cout << "\n*** TestTuple start ***\n";
    std::cout << "STuple iter tests start.\n";

    STuple<std::string, int, double> t("Alice", 25, 72.5);

    std::cout << get<0>(t) << " is "
              << get<1>(t) << " years old, weight "
              << get<2>(t) << " kg.\n";

    //STuple<> empty; // works too

    std::cout << "STuple iter tests End.\n";
    std::cout << "*** TestTuple end ***\n";
}

/**
 * @brief Executes all SPair and STuple-related tests.
 * @remark This method runs the full tuple and pair test sequence in order.
 * @return void
 */
void sTuplePairTester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running all SPair/STuple tests...\n";
    std::cout << "==============================\n";

    TestSPair();
    TestTuple();

    std::cout << "\n==============================\n";
    std::cout << "All SPair/STuple tests completed successfully.\n";
    std::cout << "==============================\n";
}