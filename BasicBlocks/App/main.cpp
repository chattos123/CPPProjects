#include <iostream>
#include <string>
#include "SMathLib.h"
#include "STestFactory.h"

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

   // Choose context
    TestContext ctx = TestContext::All;

     // Get testers from factory
    std::vector<std::unique_ptr<ITestRunner>> testers = STestFactory::CreateTesters(ctx);

    // Run all testers in the list with null check
    if(testers.empty() == false)
    {
        for (std::unique_ptr<ITestRunner>& tester : testers)
        {
            if (tester) 
            {
                tester->RunAllTests();
            } 
            else 
            {
                std::cout << "Null tester encountered, skipping...\n";
            }
        }
    }

    return 0;
}

