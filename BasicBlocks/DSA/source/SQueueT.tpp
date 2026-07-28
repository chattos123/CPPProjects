/**
 * @file SQueueT.tpp
 * @brief Implementation details for the generic SQueueT template class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SQueueT.h"
#include <stdexcept>

/**
 * @brief Inserts a new element at the rear of the queue.
 *
 * Places the element at offset `frontIndex + count` within the static array buffer and increments `count`.
 *
 * @tparam T Type of elements stored in the queue.
 * @param[in] value Constant reference to the element value to enqueue.
 * @return void
 * @throws std::runtime_error If the queue is full (`isFull() == true`).
 * @remark Operates with O(1) time complexity.
 */
template <typename T>
void SQueueT<T>::enqueue(const T& value) 
{
    if (isFull()) 
    {
        throw std::runtime_error("Queue overflow");
    }
    data[frontIndex + count] = value;
    ++count;
}

/**
 * @brief Removes and returns the element at the front of the queue.
 *
 * Advances `frontIndex` and decrements `count`. Resets `frontIndex` back to 0 whenever the queue becomes completely empty.
 *
 * @tparam T Type of elements stored in the queue.
 * @param None
 * @return T The element value previously residing at the front of the queue.
 * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
 * @remark Operates with O(1) time complexity.
 */
template <typename T>
T SQueueT<T>::dequeue() 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Queue underflow");
    }
    T value = data[frontIndex];
    ++frontIndex;
    --count;

    // Reset indices when queue becomes empty to reclaim array headroom
    if (count == 0) 
    {
        frontIndex = 0;
    }

    return value;
}

/**
 * @brief Accesses the element currently at the front of the queue without removing it.
 *
 * @tparam T Type of elements stored in the queue.
 * @param None
 * @return T Value of the front element.
 * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
 * @remark Non-destructive inspection method providing O(1) time complexity.
 */
template <typename T>
T SQueueT<T>::front() const 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Queue is empty");
    }
    
    return data[frontIndex];
}