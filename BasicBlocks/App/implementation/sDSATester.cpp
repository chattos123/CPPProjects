#include "sDSATester.h"

void sDSATester::Setup() {
    std::cout << "\nSetting up DSA test suite...\n";

    testers.emplace_back(std::make_unique<sHashTester>());
    testers.emplace_back(std::make_unique<sStackTester>());
    testers.emplace_back(std::make_unique<sListTester>());
    testers.emplace_back(std::make_unique<sVectorTester>());
    testers.emplace_back(std::make_unique<sQueueTester>());
    testers.emplace_back(std::make_unique<sTuplePairTester>());
    testers.emplace_back(std::make_unique<sStringTester>());

    std::cout << "Setup complete. " << testers.size() << " testers registered.\n";
}

void sDSATester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running all DSA tests...\n";
    std::cout << "==============================\n";

    Setup();

    for (auto& tester : testers) {
        tester->RunAllTests();
    }

    std::cout << "\n==============================\n";
    std::cout << "All DSA tests completed successfully.\n";
    std::cout << "==============================\n";
}
