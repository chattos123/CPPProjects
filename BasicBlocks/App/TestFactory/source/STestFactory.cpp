#include "STestFactory.h"

std::vector<std::unique_ptr<ITestRunner>> STestFactory::CreateTesters(TestContext ctx) {
    std::vector<std::unique_ptr<ITestRunner>> testers;

    switch (ctx) {
        case TestContext::Math:
            std::cout << "Factory: Providing Math testers...\n";
            testers.emplace_back(std::make_unique<sMathTester>());
            break;

        case TestContext::DSA:
            std::cout << "Factory: Providing DSA testers...\n";
            testers.emplace_back(std::make_unique<sDSATester>());
            break;

        case TestContext::All:
            std::cout << "Factory: Providing ALL testers (Math + DSA)...\n";
            testers.emplace_back(std::make_unique<sMathTester>());
            testers.emplace_back(std::make_unique<sDSATester>());
            break;

        default:
            std::cout << "Factory: Invalid context, no testers created.\n";
            break;
    }

    return testers;
}