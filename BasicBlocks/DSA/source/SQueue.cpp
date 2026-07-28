/**
 * @file SQueue.cpp
 * @brief Implementation of the fixed-capacity SQueue class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SQueue.h"
#include <stdexcept>

/**
 * @brief Constructs an empty SQueue instance.
 *
 * Initializes `frontIndex` to 0 and `rearIndex` to -1 to represent an empty static array buffer.
 *
 * @param None
 */
SQueue::SQueue() : frontIndex(0), rearIndex(-1) {}

/**
 * @brief Inserts a new integer value at the rear of the queue.
 *
 * Increments `rearIndex` and stores the provided value in the static array buffer.
 *
 * @param[in] value Integer value to append to the queue.
 * @return void
 * @throws std::runtime_error If the queue is full (`isFull() == true`).
 * @remark Operates with O(1) time complexity.
 */
void SQueue::enqueue(int value) 
{
    if (isFull()) 
    {
        throw std::runtime_error("Queue overflow");
    }
    data[++rearIndex] = value;
}

/**
 * @brief Removes and returns the integer value at the front of the queue.
 *
 * Retrieves the element at `frontIndex` and advances the front index pointer.
 *
 * @param None
 * @return int The integer value previously residing at the front of the queue.
 * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
 * @remark Operates with O(1) time complexity.
 */
int SQueue::dequeue() 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Queue underflow");
    }

    int value = data[frontIndex++];
    return value;
}

/**
 * @brief Accesses the integer value currently at the front of the queue without removing it.
 *
 * @param None
 * @return int Value of the front element.
 * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
 * @remark Non-destructive inspection method providing O(1) time complexity.
 */
int SQueue::front() const 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Queue is empty");
    }
    return data[frontIndex];
}

/**
 * @brief Checks whether the queue currently contains no elements.
 *
 * Evaluates whether the front index has progressed past the rear index.
 *
 * @param None
 * @return true If `frontIndex > rearIndex`.
 * @return false If active elements remain in the queue.
 * @remark Query method providing O(1) time complexity.
 */
bool SQueue::isEmpty() const 
{
    return frontIndex > rearIndex;
}

/**
 * @brief Checks whether the queue has reached its maximum static storage capacity (`QUEUE_MAX`).
 *
 * @param None
 * @return true If `rearIndex == QUEUE_MAX - 1`.
 * @return false If buffer space remains available for additional element enqueues.
 * @remark Query method providing O(1) time complexity.
 */
bool SQueue::isFull() const 
{
    return rearIndex == QUEUE_MAX - 1;
}