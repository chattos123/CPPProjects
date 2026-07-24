#include "sStackTester.h"

void sStackTester::TestStack() {
    std::cout << "\n*** TestStack start ***\n";
    SStack stack;
    stack.push(10);
    stack.push(20);
    std::cout << "Top element: " << stack.top() << "\n";
    stack.pop();
    std::cout << "Top element after pop: " << stack.top() << "\n";
    std::cout << "*** TestStack end ***\n";
}

void sStackTester::TestStackT() {
    std::cout << "\n*** TestStackT start ***\n";

    SStackT<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    std::cout << "Top element: " << intStack.top() << "\n";
    intStack.display();
    intStack.pop();
    std::cout << "Top element after pop: " << intStack.top() << "\n";
    intStack.display();

    SStackT<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "Top element: " << stringStack.top() << "\n";
    stringStack.display();
    stringStack.pop();
    std::cout << "Top element after pop: " << stringStack.top() << "\n";
    stringStack.display();

    std::cout << "*** TestStackT end ***\n";
}

void sStackTester::TestListStack() {
    std::cout << "\n*** TestListStack start ***\n";

    SListStackT<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    std::cout << "Top element: " << intStack.top() << "\n";
    intStack.display();
    intStack.pop();
    std::cout << "Top element after pop: " << intStack.top() << "\n";
    intStack.display();

    SListStackT<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "Top element: " << stringStack.top() << "\n";
    stringStack.display();
    stringStack.pop();
    std::cout << "Top element after pop: " << stringStack.top() << "\n";
    stringStack.display();

    std::cout << "*** TestListStack end ***\n";
}

void sStackTester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running all Stack tests...\n";
    std::cout << "==============================\n";

    TestStack();
    TestStackT();
    TestListStack();

    std::cout << "\n==============================\n";
    std::cout << "All Stack tests completed successfully.\n";
    std::cout << "==============================\n";
}
