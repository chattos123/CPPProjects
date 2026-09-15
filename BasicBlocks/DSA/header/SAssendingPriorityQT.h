/*
 * File: SAssendingPriorityQT.h
 * @brief Declares the generic ascending priority queue template class.
 * Author: Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"
#include "SListT.h"
#include <stdexcept>

/**
 * @class SAssendingPriorityQT
 * @brief Ascending priority queue adapter built on top of SListT<T>.
 *
 * Maintains elements in ascending order. The smallest element
 * is always dequeued first. Insertions traverse the list to
 * place new elements in sorted position.
 *
 * @tparam T Element type stored in the queue. Requires operator<.
 */
/*Key Characteristics
Ascending order maintained: Enqueue traverses the list to insert in sorted position.

Front = smallest element: Dequeue always removes the smallest.

Complexity:

Enqueue: O(n) (traversal).

Dequeue: O(1).

Front: O(1).

Move semantics: Delegated to SListT.

Error handling: Throws on empty operations.
*/
template <typename T>
class SAssendingPriorityQT 
{
private:
    SListT<T> m_list; ///< Underlying singly-linked list.

public:
    /**
     * @brief Constructs an empty ascending priority queue.
     */
    SAssendingPriorityQT() = default;

    /**
     * @brief Destructor; underlying SListT frees nodes.
     */
    ~SAssendingPriorityQT() = default;

    /**
     * @brief Copy constructor (deep copy).
     */
    SAssendingPriorityQT(const SAssendingPriorityQT& other) = default;

    /**
     * @brief Copy assignment operator (deep copy).
     */
    SAssendingPriorityQT& operator=(const SAssendingPriorityQT& other) = default;

    /**
     * @brief Move constructor.
     */
    SAssendingPriorityQT(SAssendingPriorityQT&& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     */
    SAssendingPriorityQT& operator=(SAssendingPriorityQT&& other) noexcept = default;

    /**
     * @brief Inserts a new element into the queue in ascending order.
     *
     * @param val Value to insert.
     * @return true if insertion succeeded; false if allocation failed.
     */
    bool Enqueue(const T& val);

    /**
     * @brief Removes and returns the smallest element (front).
     *
     * @throws std::out_of_range if empty.
     * @return The smallest element.
     */
    T Dequeue();

    /**
     * @brief Returns the smallest element without removing it.
     *
     * @throws std::out_of_range if empty.
     * @return The smallest element.
     */
    T Front() const;

    /**
     * @brief Checks if the queue is empty.
     */
    bool IsEmpty() const { return m_list.IsEmpty(); }

    /**
     * @brief Returns the number of elements.
     */
    int Size() const { return m_list.GetLength(); }

    /**
     * @brief Displays all elements in ascending order.
     */
    bool Display() { return m_list.Display(); }
};

// include implementation
#include "SAssendingPriorityQT.tpp"
