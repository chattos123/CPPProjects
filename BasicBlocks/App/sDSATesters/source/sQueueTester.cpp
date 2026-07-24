// sQueueTester.cpp
#include "sQueueTester.h"

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
