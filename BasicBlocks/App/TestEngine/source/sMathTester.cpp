#include "sMathTester.h"

void sMathTester::Setup() 
{
    std::cout << "\nSetting up Math test suite...\n";
    testers.emplace_back(std::make_unique<sCalcTester>());
    testers.emplace_back(std::make_unique<sComplexTester>());

    std::cout << "Setup complete. " << testers.size() << " testers registered.\n";
}

void sMathTester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running Math tests...\n";
    std::cout << "==============================\n";

    Setup();

    for (auto& tester : testers) {
        tester->RunAllTests();
    }

    std::cout << "\n==============================\n";
    std::cout << "All Math tests completed successfully.\n";
    std::cout << "==============================\n";
}