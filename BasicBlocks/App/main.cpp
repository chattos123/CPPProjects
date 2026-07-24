#include <iostream>
#include <string>
#include "SMathLib.h"
#include "SCalculator.h"
#include "SComplex.h"
#include "sDSATester.h"


// Testing app
void TestCalculator();
void TestComplex();


int main() {

        std::cout << "Calculator App Version: ";
    #ifdef PROJECT_VERSION
        std::cout << PROJECT_VERSION;
    #else
        std::cout << "unknown";
    #endif
        std::cout << std::endl;

    // You can also use it in conditional compilation:
#if defined(PROJECT_VERSION)
    std::cout << "Build stamped with version info." << std::endl;
#else
    std::cout << "No version info available." << std::endl;
#endif
    std::cout << "Calling DLL function..." << std::endl;
    helloFromDLL();

    //Test calculator
    TestCalculator();

    //Test complex
    TestComplex();

    ITestRunner* runner = new sDSATester();
    runner->RunAllTests();
    delete runner;

    return 0;
}

void TestCalculator()
{
    std::cout << "***Testing SCalculator...***\n";
    SCalculator calc;

    double a = 10.0, b = 5.0;

    std::cout << "Add: " << calc.add(a, b) << "\n";
    std::cout << "Subtract: " << calc.subtract(a, b) << "\n";
    std::cout << "Multiply: " << calc.multiply(a, b) << "\n";
    std::cout << "Divide: " << calc.divide(a, b) << "\n";
    std::cout << "Modulo: " << calc.mod(a, b) << "\n";

    std::cout << "***SCalculator tests completed.***\n";
}

/*void TestComplex()
{
    std::cout << "Testing SComplex...\n";

    SComplex C1(3.0, 4.0);
    SComplex C2(1.0, -2.0);
    std::cout << "C1: ";
    C1.display();
    std::cout << "C2: ";
    C2.display();

    SComplex sum = C1 + C2;
    sum.display();

    SComplex prod = C1 * C2;
    prod.display();

    //SComplex scaled = C1 * 2;
    //scaled.display();

    C1.display();

    std::cout << "SComplex tests completed.\n";
}*/

void TestComplex()
{
    std::cout << "***Testing Complex class...***\n";

    // Create some complex numbers
    SComplex c1(3.0, 4.0);   // 3 + 4i
    SComplex c2(1.0, 2.0);   // 1 + 2i

    // Display them
    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";

    // Addition
    SComplex sum = c1 + c2;
    std::cout << "c1 + c2 = " << sum << "\n";

    // Subtraction
    SComplex diff = c1 - c2;
    std::cout << "c1 - c2 = " << diff << "\n";

    // Multiplication
    SComplex prod = c1 * c2;
    std::cout << "c1 * c2 = " << prod << "\n";

    // Division
    SComplex quot = c1 / c2;
    std::cout << "c1 / c2 = " << quot << "\n";

    // Magnitude
    //std::cout << "|c1| = " << c1.magnitude() << "\n";

    // Equality check
    //std::cout << "c1 == c2 ? " << (c1 == c2 ? "true" : "false") << "\n";

    std::cout << "Complex class tests completed.***\n\n";
}



