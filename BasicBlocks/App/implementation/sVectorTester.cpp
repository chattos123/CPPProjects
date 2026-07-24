#include "sVectorTester.h"

void sVectorTester::TestVector() {
    std::cout << "\n*** TestVector start ***\n";
    std::cout << "***Testing SVector...***\n";

    SVector vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.display(); // [ 10 20 30 ]
    std::cout << "Element at index 1: " << vec.at(1) << "\n";

    vec.pop_back();
    vec.display(); // [ 10 20 ]

    vec[0] = 100;
    vec.display(); // [ 100 20 ]

    int p = vec[1];
    std::cout << "x = " << p << "\n";

    SVector v1;
    v1.push_back(1);
    v1.push_back(2);

    SVector v2;
    v2.push_back(3);
    v2.push_back(4);

    SVector v3(v1);   // Copy constructor
    v3.display();

    SVector v4;
    v4 = v2;          // Assignment
    v4.display();

    SVector v5 = v1 + v2; // Addition
    v5.display();

    std::cout << "***SVector tests completed.***\n";
    std::cout << "*** TestVector end ***\n";
}

void sVectorTester::TestVectorT() {
    std::cout << "\n*** TestVectorT start ***\n";
    std::cout << "Testing SVectorT...\n";

    SVectorT<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.display();
    std::cout << "Element at index 1: " << vec.at(1) << "\n";

    vec.pop_back();
    vec.display();

    vec[0] = 100;
    vec.display();

    int x = vec[1];
    std::cout << "x = " << x << "\n";

    SVectorT<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    SVectorT<int> v2;
    v2.push_back(3);
    v2.push_back(4);

    SVectorT<int> v3(v1);   // Copy constructor
    v3.display();

    SVectorT<int> v4;
    v4 = v2;                // Assignment
    v4.display();

    SVectorT<int> v5 = v1 + v2; // Addition
    v5.display();

    std::cout << "Iterating over v5 using iterators:\n";
    for (auto it = v5.begin(); it != v5.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "***SVectorT tests completed.***\n";
    std::cout << "*** TestVectorT end ***\n";
}

void sVectorTester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running all Vector tests...\n";
    std::cout << "==============================\n";

    TestVector();
    TestVectorT();

    std::cout << "\n==============================\n";
    std::cout << "All Vector tests completed successfully.\n";
    std::cout << "==============================\n";
}
