#include "sTuplePairTester.h"

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

void sTuplePairTester::TestTuple() {
    std::cout << "\n*** TestTuple start ***\n";
    std::cout << "STuple iter tests start.\n";

    STuple<std::string, int, double> t("Alice", 25, 72.5);

    std::cout << get<0>(t) << " is "
              << get<1>(t) << " years old, weight "
              << get<2>(t) << " kg.\n";

    STuple<> empty; // works too

    std::cout << "STuple iter tests End.\n";
    std::cout << "*** TestTuple end ***\n";
}

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