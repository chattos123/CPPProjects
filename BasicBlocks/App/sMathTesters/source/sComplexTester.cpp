#include "sComplexTester.h"

void sComplexTester::TestComplex() {
    std::cout << "\n*** Complex Test start ***\n";

    SComplex c1(3.0, 4.0);
    SComplex c2(1.0, 2.0);

    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";

    std::cout << "c1 + c2 = " << (c1 + c2) << "\n";
    std::cout << "c1 - c2 = " << (c1 - c2) << "\n";
    std::cout << "c1 * c2 = " << (c1 * c2) << "\n";
    std::cout << "c1 / c2 = " << (c1 / c2) << "\n";

    std::cout << "*** Complex Test end ***\n\n";
}

void sComplexTester::RunAllTests() {
    std::cout << "Running SComplex tests...\n";
    TestComplex();
}
