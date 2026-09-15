/*
 * File: sQueueTester.cpp
 * Author: Soumyajit C
 * Description: Implements the queue-related tester methods for the application.
 */

#include "sQueueTester.h"
#include <chrono>

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
 * @brief Tests the behavior of the ascending priority queue (SAssendingPriorityQT).
 */
void sQueueTester::TestSAssendingPriorityQT() 
{
    std::cout << "***Testing SAssendingPriorityQT<int>...***\n";
    SAssendingPriorityQT<int> pq;
    pq.Enqueue(30);
    pq.Enqueue(10);
    pq.Enqueue(20);

    std::cout << "Front element (smallest): " << pq.Front() << "\n"; // should be 10
    std::cout << "Dequeue: " << pq.Dequeue() << "\n";                // removes 10
    std::cout << "Front element after dequeue: " << pq.Front() << "\n"; // should be 20

    std::cout << "***Testing SAssendingPriorityQT<std::string>...***\n";
    SAssendingPriorityQT<std::string> strPQ;
    strPQ.Enqueue("Gamma");
    strPQ.Enqueue("Alpha");
    strPQ.Enqueue("Beta");

    std::cout << "Front element (alphabetically smallest): " << strPQ.Front() << "\n"; // should be "Alpha"
    std::cout << "Dequeue: " << strPQ.Dequeue() << "\n";                               // removes "Alpha"
    std::cout << "Front element after dequeue: " << strPQ.Front() << "\n";             // should be "Beta"

    std::cout << "***SAssendingPriorityQT tests completed.***\n\n";
}

/**
 * @brief Tests exception handling (underflow/empty ops) for SAssendingPriorityQT.
 */
void sQueueTester::TestSAssendingPriorityQTNegative() 
{
    std::cout << "***Testing SAssendingPriorityQT Negative Cases...***\n";
    SAssendingPriorityQT<int> pq;

    // Dequeue on empty
    try 
    {
        std::cout << "Attempting Dequeue on empty priority queue...\n";
        pq.Dequeue();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Front on empty
    try 
    {
        std::cout << "Attempting Front on empty priority queue...\n";
        pq.Front();
    } catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Add some elements, then clear by dequeuing all
    pq.Enqueue(5);
    pq.Enqueue(1);
    pq.Enqueue(3);

    std::cout << "Dequeued: " << pq.Dequeue() << "\n"; // 1
    std::cout << "Dequeued: " << pq.Dequeue() << "\n"; // 3
    std::cout << "Dequeued: " << pq.Dequeue() << "\n"; // 5

    // Now empty again, try Dequeue
    try 
    {
        std::cout << "Attempting Dequeue after clearing priority queue...\n";
        pq.Dequeue();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "***SAssendingPriorityQT Negative tests completed.***\n\n";
}

/**
 * @brief Performance benchmark for SAssendingPriorityQT under bulk operations.
 */
void sQueueTester::TestSAssendingPriorityQTPerformance() 
{
    std::cout << "***Performance Test: SAssendingPriorityQT<int>...***\n";
    SAssendingPriorityQT<int> pq;

    const int N = 20000; // adjust size for stress test
    auto start = std::chrono::high_resolution_clock::now();

    // Bulk enqueue in random order
    for (int i = N; i > 0; --i) 
    {
        pq.Enqueue(i);
    }

    auto mid = std::chrono::high_resolution_clock::now();

    // Bulk dequeue
    for (int i = 0; i < N; ++i)
    {
        pq.Dequeue();
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto enqueueTime = std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count();
    auto dequeueTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count();

    std::cout << "Enqueue " << N << " elements took: " << enqueueTime << " ms\n";
    std::cout << "Dequeue " << N << " elements took: " << dequeueTime << " ms\n";
    std::cout << "***SAssendingPriorityQT Performance test completed.***\n\n";
}

/**
 * @brief Tests the behavior of the descending priority queue (SDecendingPriorityQT).
 */
void sQueueTester::TestSDecendingPriorityQT() 
{
    std::cout << "***Testing SDecendingPriorityQT<int>...***\n";
    SDecendingPriorityQT<int> pq;
    pq.Enqueue(10);
    pq.Enqueue(30);
    pq.Enqueue(20);

    std::cout << "Front element (largest): " << pq.Front() << "\n"; // should be 30
    std::cout << "Dequeue: " << pq.Dequeue() << "\n";               // removes 30
    std::cout << "Front element after dequeue: " << pq.Front() << "\n"; // should be 20

    std::cout << "***Testing SDecendingPriorityQT<std::string>...***\n";
    SDecendingPriorityQT<std::string> strPQ;
    strPQ.Enqueue("Alpha");
    strPQ.Enqueue("Gamma");
    strPQ.Enqueue("Beta");

    std::cout << "Front element (alphabetically largest): " << strPQ.Front() << "\n"; // should be "Gamma"
    std::cout << "Dequeue: " << strPQ.Dequeue() << "\n";                              // removes "Gamma"
    std::cout << "Front element after dequeue: " << strPQ.Front() << "\n";            // should be "Beta"

    std::cout << "***SDecendingPriorityQT tests completed.***\n\n";
}

/**
 * @brief Tests exception handling (underflow/empty ops) for SDecendingPriorityQT.
 */
void sQueueTester::TestSDecendingPriorityQTNegative() 
{
    std::cout << "***Testing SDecendingPriorityQT Negative Cases...***\n";
    SDecendingPriorityQT<int> pq;

    // Dequeue on empty
    try 
    {
        std::cout << "Attempting Dequeue on empty descending priority queue...\n";
        pq.Dequeue();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Front on empty
    try {
        std::cout << "Attempting Front on empty descending priority queue...\n";
        pq.Front();
    } 
    catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Add some elements, then clear by dequeuing all
    pq.Enqueue(100);
    pq.Enqueue(50);
    pq.Enqueue(75);

    std::cout << "Dequeued: " << pq.Dequeue() << "\n"; // 100
    std::cout << "Dequeued: " << pq.Dequeue() << "\n"; // 75
    std::cout << "Dequeued: " << pq.Dequeue() << "\n"; // 50

    // Now empty again, try Dequeue
    try 
    {
        std::cout << "Attempting Dequeue after clearing descending priority queue...\n";
        pq.Dequeue();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "***SDecendingPriorityQT Negative tests completed.***\n\n";
}

/**
 * @brief Performance benchmark for SDecendingPriorityQT under bulk operations.
 */
void sQueueTester::TestSDecendingPriorityQTPerformance() 
{
    std::cout << "***Performance Test: SDecendingPriorityQT<int>...***\n";
    SDecendingPriorityQT<int> pq;

    const int N = 50000; // adjust size for stress test
    auto start = std::chrono::high_resolution_clock::now();

    // Bulk enqueue in random order
    for (int i = 0; i < N; ++i) 
    {
        pq.Enqueue(rand() % N);
    }

    auto mid = std::chrono::high_resolution_clock::now();

    // Bulk dequeue
    for (int i = 0; i < N; ++i) {
        pq.Dequeue();
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto enqueueTime = std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count();
    auto dequeueTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count();

    std::cout << "Enqueue " << N << " elements took: " << enqueueTime << " ms\n";
    std::cout << "Dequeue " << N << " elements took: " << dequeueTime << " ms\n";
    std::cout << "***SDecendingPriorityQT Performance test completed.***\n\n";
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
    TestSAssendingPriorityQT();
    TestSAssendingPriorityQTNegative();
    TestSAssendingPriorityQTPerformance();
    TestSDecendingPriorityQT();
    TestSDecendingPriorityQTNegative();
    TestSDecendingPriorityQTPerformance();

    std::cout << "==============================\n";
    std::cout << "Queue tests completed.\n";
    std::cout << "==============================\n";
}
