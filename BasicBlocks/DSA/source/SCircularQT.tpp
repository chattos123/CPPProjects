/**
 * @file SCircularQT.tpp
 * @brief Implementation details for the generic SCircularQT template class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SCircularQT.h"
#include <stdexcept>



/**
 * @brief Inserts a new element at the rear of the queue.
 *
 * Advances `rearIndex` using modular arithmetic and stores the element in the buffer.
 *
 * @tparam T Type of elements stored in the queue.
 * @param[in] value Constant reference to the element value to enqueue.
 * @throws std::runtime_error If the queue is full (`isFull() == true`).
 */
template <typename T>
void SCircularQT<T>::enqueue(const T& value) 
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
 * @brief Removes and returns the element at the front of the queue.
 *
 * Retrieves the element at `frontIndex`, advances it using modular arithmetic, and decrements `count`.
 *
 * @tparam T Type of elements stored in the queue.
 * @return T The element value previously residing at the front of the queue.
 * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
 */
template <typename T>
T SCircularQT<T>::dequeue() 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Circular queue underflow");
    }
    T value = data[frontIndex];
    frontIndex = (frontIndex + 1) % QUEUE_MAX;
    --count;
    return value;
}

/**
 * @brief Accesses the element currently at the front of the queue without removing it.
 *
 * @tparam T Type of elements stored in the queue.
 * @return T Value of the front element.
 * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
 */
template <typename T>
T SCircularQT<T>::front() const 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("Circular queue is empty");
    }
    return data[frontIndex];
}

/**
 * @brief Copy constructor for SCircularQT.
 *
 * Initializes a new queue instance by copying indices, count, and all elements from `other`.
 *
 * @tparam T Type of elements stored in the queue.
 * @param[in] other Reference to another SCircularQT instance to copy from.
 */
template <typename T>
SCircularQT<T>::SCircularQT(const SCircularQT<T>& other)
    : frontIndex(other.frontIndex),
      rearIndex(other.rearIndex),
      count(other.count)
{
    for (int i = 0; i < QUEUE_MAX; ++i) 
    {
        data[i] = other.data[i];
    }
}

/**
 * @brief Copy assignment operator for SCircularQT.
 *
 * Replaces the contents of this queue with those of `other`.
 *
 * @tparam T Type of elements stored in the queue.
 * @param[in] other Reference to another SCircularQT instance to assign from.
 * @return Reference to this SCircularQT instance.
 */
template <typename T>
SCircularQT<T>& SCircularQT<T>::operator=(const SCircularQT<T>& other)
{
    if (this == &other) {
        return *this; // self-assignment check
    }

    frontIndex = other.frontIndex;
    rearIndex  = other.rearIndex;
    count      = other.count;

    for (int i = 0; i < QUEUE_MAX; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

/**
 * @brief Move constructor for SCircularQT.
 *
 * Transfers ownership of indices, count, and buffer contents from `other` into this queue.
 * Resets `other` to an empty state.
 *
 * @tparam T Type of elements stored in the queue.
 * @param[in] other Rvalue reference to another SCircularQT instance.
 */
template <typename T>
SCircularQT<T>::SCircularQT(SCircularQT<T>&& other) noexcept
    : frontIndex(other.frontIndex),
      rearIndex(other.rearIndex),
      count(other.count)
{
    for (int i = 0; i < QUEUE_MAX; ++i) {
        data[i] = std::move(other.data[i]);
    }

    // Reset source queue
    other.frontIndex = 0;
    other.rearIndex  = -1;
    other.count      = 0;
}

/**
 * @brief Move assignment operator for SCircularQT.
 *
 * Transfers ownership of indices, count, and buffer contents from `other` into this queue.
 * Resets `other` to an empty state.
 *
 * @tparam T Type of elements stored in the queue.
 * @param[in] other Rvalue reference to another SCircularQT instance.
 * @return Reference to this SCircularQT instance.
 */
template <typename T>
SCircularQT<T>& SCircularQT<T>::operator=(SCircularQT<T>&& other) noexcept
{
    if (this == &other) {
        return *this; // self-assignment check
    }

    frontIndex = other.frontIndex;
    rearIndex  = other.rearIndex;
    count      = other.count;

    for (int i = 0; i < QUEUE_MAX; ++i) {
        data[i] = std::move(other.data[i]);
    }

    // Reset source queue
    other.frontIndex = 0;
    other.rearIndex  = -1;
    other.count      = 0;

    return *this;
}

