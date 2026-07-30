/**
 * @file SCircularQ.cpp
 * @brief Implementation of the fixed-capacity SCircularQ class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SCircularQ.h"
#include <stdexcept>

/**
 * @brief Constructs an empty SCircularQ instance.
 */
SCircularQ::SCircularQ() : frontIndex(0), rearIndex(-1), count(0) {}

/**
 * @brief Inserts a new integer value at the rear of the queue.
 */
void SCircularQ::enqueue(int value) 
{
    if (isFull()) 
    {
        throw std::runtime_error("Circular queue overflow");
    }

    rearIndex = (rearIndex + 1) % QUEUE_MAX;
    data[rearIndex] = value;
    ++count;
}

/**
 * @brief Removes and returns the integer value at the front of the queue.
 */
int SCircularQ::dequeue() 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Circular queue underflow");
    }

    int value = data[frontIndex];
    frontIndex = (frontIndex + 1) % QUEUE_MAX;
    --count;
    return value;
}

/**
 * @brief Accesses the integer value currently at the front of the queue.
 */
int SCircularQ::front() const 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Circular queue is empty");
    }
    return data[frontIndex];
}

/**
 * @brief Checks whether the queue currently contains no elements.
 */
bool SCircularQ::isEmpty() const 
{
    return count == 0;
}

/**
 * @brief Checks whether the queue has reached its maximum static storage capacity.
 */
bool SCircularQ::isFull() const 
{
    return count == QUEUE_MAX;
}
