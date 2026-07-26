/*
 * File: sListTester.cpp
 * Author: Soumyajit C
 * Description: Implements the list-related tester methods for the application.
 */

#include "sListTester.h"

/**
 * @brief Tests the behavior of the SList container.
 */
void sListTester::TestList() 
{
    std::cout << "\n*** TestList start ***\n";
    std::cout << "***Testing SList...***\n";

    SList list;
    list.AddElement(5);
    list.AddElement(10);
    list.AddElement(15);
    list.Display();

    list.AddElementAfter(1, 12); // Add 12 after the second element
    list.Display();

    list.DeleteElement(); // Delete the last element
    list.Display();

    std::cout << "***SList tests completed.***\n";
    std::cout << "*** TestList end ***\n";
}

/**
 * @brief Tests the behavior of the templated SListT container.
 */
void sListTester::TestListT() 
{
    std::cout << "\n*** TestListT start ***\n";
    std::cout << "***Testing SListT...***\n";

    // int list
    SListT<int> intList;
    intList.AddElement(10);
    intList.AddElement(20);
    intList.AddElement(30);
    intList.Display();

    // string list
    SListT<std::string> stringList;
    stringList.AddElement("Hello");
    stringList.AddElement("World");
    stringList.Display();

    std::cout << "***SListT tests completed.***\n";
    std::cout << "*** TestListT end ***\n";
}

/**
 * @brief Executes all list-related tests.
 */
void sListTester::RunAllTests() 
{
    std::cout << "\n==============================\n";
    std::cout << "Running all List tests...\n";
    std::cout << "==============================\n";

    TestList();
    TestListT();

    std::cout << "\n==============================\n";
    std::cout << "All List tests completed successfully.\n";
    std::cout << "==============================\n";
}
