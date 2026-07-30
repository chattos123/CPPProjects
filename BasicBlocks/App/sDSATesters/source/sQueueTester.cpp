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
 * @brief Tests the behavior of the SCircularQ container.
 */
void sQueueTester::TestCircularQ() 
{
    std::cout << "***Testing SCircularQ...***\n";
    SCircularQ queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "Front element: " << queue.front() << "\n";
    std::cout << "Dequeue: " << queue.dequeue() << "\n";
    std::cout << "Front element after dequeue: " << queue.front() << "\n";
    std::cout << "***SCircularQ tests completed.***\n\n";
}

/**
 * @brief Tests the behavior of the templated SCircularQT container.
 */
void sQueueTester::TestCircularQT() 
{
    std::cout << "***Testing SCircularQT<int>...***\n";
    SCircularQT<int> queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    std::cout << "Front element: " << queue.front() << "\n";
    std::cout << "Dequeue: " << queue.dequeue() << "\n";
    std::cout << "Front element after dequeue: " << queue.front() << "\n";

    std::cout << "***Testing SCircularQT<std::string>...***\n";
    SCircularQT<std::string> strQueue;
    strQueue.enqueue("Alpha");
    strQueue.enqueue("Beta");
    strQueue.enqueue("Gamma");
    std::cout << "Front element: " << strQueue.front() << "\n";
    std::cout << "Dequeue: " << strQueue.dequeue() << "\n";
    std::cout << "Front element after dequeue: " << strQueue.front() << "\n";
    std::cout << "***SCircularQT tests completed.***\n\n";
}

/**
 * @brief Tests iterator traversal for SCircularQT.
 */
void sQueueTester::TestCircularQTIterators() 
{
    std::cout << "***Testing SCircularQT Iterators...***\n";
    SCircularQT<int> queue;

    for (int i = 1; i <= 5; ++i) 
    {
        queue.enqueue(i * 10);
    }

    std::cout << "Iterating over queue elements: ";

    for (auto& val : queue) 
    {
        std::cout << val << " ";
    }
    std::cout << "\n***Iterator test completed.***\n\n";
}

/**
 * @brief Tests exception handling (overflow/underflow) for SCircularQT.
 */
void sQueueTester::TestCircularQTNegative() 
{
    std::cout << "***Testing SCircularQT Negative Cases...***\n";
    SCircularQT<int> queue;

    // Underflow test
    try 
    {
        std::cout << "Attempting dequeue on empty queue...\n";
        queue.dequeue();
    } 
    catch (const std::runtime_error& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Fill queue to capacity
    for (int i = 0; i < QUEUE_MAX; ++i) 
    {
        queue.enqueue(i);
    }

    // Overflow test
    try 
    {
        std::cout << "Attempting enqueue on full queue...\n";
        queue.enqueue(999);
    } 
    catch (const std::runtime_error& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "***Negative tests completed.***\n\n";
}

/**
 * @brief Tests the behavior of the SListQT container.
 */
void sQueueTester::TestSListQT() 
{
    std::cout << "***Testing SListQT<int>...***\n";
    SListQT<int> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);

    std::cout << "Front element: " << queue.GetHead()->m_val << "\n";
    std::cout << "Dequeue: " << queue.Dequeue() << "\n";
    std::cout << "Front element after dequeue: " << queue.GetHead()->m_val << "\n";

    std::cout << "***Testing SListQT<std::string>...***\n";
    SListQT<std::string> strQueue;
    strQueue.Enqueue("Alpha");
    strQueue.Enqueue("Beta");
    strQueue.Enqueue("Gamma");

    std::cout << "Front element: " << strQueue.GetHead()->m_val << "\n";
    std::cout << "Dequeue: " << strQueue.Dequeue() << "\n";
    std::cout << "Front element after dequeue: " << strQueue.GetHead()->m_val << "\n";

    std::cout << "***SListQT tests completed.***\n\n";
}

/**
 * @brief Tests the behavior of the SListCircularQT container.
 */
void sQueueTester::TestSListCircularQT() 
{
    std::cout << "***Testing SListCircularQT<int>...***\n";
    SListCircularQT<int> queue;
    queue.PushBack(1);
    queue.PushBack(2);
    queue.PushBack(3);

    std::cout << "Front element: " << queue.PopFront() << "\n"; // removes 1
    queue.PushFront(0); // add new head
    std::cout << "Front element after PushFront: " << queue.PopFront() << "\n"; // removes 0

    queue.Rotate(); // rotate once
    std::cout << "Front element after Rotate: " << queue.PopFront() << "\n";

    std::cout << "***Testing SListCircularQT<std::string>...***\n";
    SListCircularQT<std::string> strQueue;
    strQueue.PushBack("Hello");
    strQueue.PushBack("World");
    strQueue.PushBack("!");

    std::cout << "Front element: " << strQueue.PopFront() << "\n";
    strQueue.PushFront("NewHead");
    std::cout << "Front element after PushFront: " << strQueue.PopFront() << "\n";

    std::cout << "***SListCircularQT tests completed.***\n\n";
}

/**
 * @brief Tests exception handling (underflow/invalid ops) for SListCircularQT.
 */
void sQueueTester::TestSListCircularQTNegative() 
{
    std::cout << "***Testing SListCircularQT Negative Cases...***\n";
    SListCircularQT<int> queue;

    // Underflow test: PopFront on empty
    try 
    {
        std::cout << "Attempting PopFront on empty list...\n";
        queue.PopFront();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Rotate on empty (should be no-op, no exception)
    std::cout << "Attempting Rotate on empty list...\n";
    queue.Rotate();
    std::cout << "Rotate on empty executed safely.\n";

    // PushBack some elements
    queue.PushBack(1);
    queue.PushBack(2);

    // PopFront until empty
    std::cout << "PopFront: " << queue.PopFront() << "\n";
    std::cout << "PopFront: " << queue.PopFront() << "\n";

    // Now empty again, try PopFront
    try 
    {
        std::cout << "Attempting PopFront after clearing list...\n";
        queue.PopFront();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "***SListCircularQT Negative tests completed.***\n\n";
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
    TestSListQT();
    TestCircularQ();
    TestCircularQT();
    TestSListCircularQT();
    TestCircularQTIterators();
    TestCircularQTNegative();

    std::cout << "==============================\n";
    std::cout << "Queue tests completed.\n";
    std::cout << "==============================\n";
}
