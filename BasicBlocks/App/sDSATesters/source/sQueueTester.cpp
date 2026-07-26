/*
 * File: sQueueTester.cpp
 * Author: Soumyajit C
 * Description: Implements the queue-related tester methods for the application.
 */

#include "sQueueTester.h"

/**
 * @brief Tests the behavior of the SQueue container.
 */
void sQueueTester::TestQueue() 
{
    std::cout << "***Testing SQueue...***\n";
    SQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    std::cout << "Front element: " << queue.front() << "\n";
    std::cout << "Dequeue: " << queue.dequeue() << "\n";
    std::cout << "Front element after dequeue: " << queue.front() << "\n";
    std::cout << "***SQueue tests completed.***\n\n";
}

/**
 * @brief Tests the behavior of the templated SQueueT container.
 */
void sQueueTester::TestQueueT() 
{
    std::cout << "***Testing SQueueT...***\n";
    SQueueT<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    std::cout << "Front element: " << queue.front() << "\n";
    std::cout << "Dequeue: " << queue.dequeue() << "\n";
    std::cout << "Front element after dequeue: " << queue.front() << "\n";

    SQueueT<std::string> strQueue;
    strQueue.enqueue("Hello");
    strQueue.enqueue("World");
    strQueue.enqueue("!");
    std::cout << "Front element: " << strQueue.front() << "\n";
    std::cout << "Dequeue: " << strQueue.dequeue() << "\n";
    std::cout << "Front element after dequeue: " << strQueue.front() << "\n";
    std::cout << "***SQueueT tests completed.***\n\n";
}

/**
 * @brief Executes all queue-related tests.
 */
void sQueueTester::RunAllTests()
{
    std::cout << "\n==============================\n";
    std::cout << "Running Queue tests...\n";
    std::cout << "==============================\n";

    TestQueue();
    TestQueueT();

    std::cout << "==============================\n";
    std::cout << "Queue tests completed.\n";
    std::cout << "==============================\n";
}
