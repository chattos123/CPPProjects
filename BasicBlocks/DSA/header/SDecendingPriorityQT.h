/*
 * File: SDecendingPriorityQT.h
 * @brief Declares the generic descending priority queue template class.
 * Author: Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"
#include "SListT.h"
#include <stdexcept>

/**
 * @class SDecendingPriorityQT
 * @brief Descending priority queue adapter built on top of SListT<T>.
 *
 * Maintains elements in descending order. The largest element
 * is always dequeued first. Insertions traverse the list to
 * place new elements in sorted position.
 *
 * @tparam T Element type stored in the queue. Requires operator<.
 *
 * ### Complexity Summary
 * - Enqueue: O(n) — traversal to find insertion point
 * - Dequeue: O(1) — remove head
 * - Front:   O(1) — access head
 * - IsEmpty: O(1)
 * - Size:    O(1)
 * - Display: O(n)
 */
template <typename T>
class SDecendingPriorityQT 
{
private:
    SListT<T> m_list; ///< Underlying singly-linked list.

public:
    /**
     * @brief Constructs an empty descending priority queue.
     * @complexity O(1)
     */
    SDecendingPriorityQT() = default;

    /**
     * @brief Destructor; underlying SListT frees nodes.
     * @complexity O(n) — deletes all nodes
     */
    ~SDecendingPriorityQT() = default;

    /**
     * @brief Copy constructor (deep copy).
     * @complexity O(n)
     */
    SDecendingPriorityQT(const SDecendingPriorityQT& other) = default;

    /**
     * @brief Copy assignment operator (deep copy).
     * @complexity O(n)
     */
    SDecendingPriorityQT& operator=(const SDecendingPriorityQT& other) = default;

    /**
     * @brief Move constructor.
     * @complexity O(1)
     */
    SDecendingPriorityQT(SDecendingPriorityQT&& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     * @complexity O(1)
     */
    SDecendingPriorityQT& operator=(SDecendingPriorityQT&& other) noexcept = default;

    /**
     * @brief Inserts a new element into the queue in descending order.
     * @param val Value to insert.
     * @return true if insertion succeeded; false if allocation failed.
     * @complexity O(n) — traversal to find correct position
     */
    bool Enqueue(const T& val);

    /**
     * @brief Removes and returns the largest element (front).
     * @throws std::out_of_range if empty.
     * @return The largest element.
     * @complexity O(1)
     */
    T Dequeue();

    /**
     * @brief Returns the largest element without removing it.
     * @throws std::out_of_range if empty.
     * @return The largest element.
     * @complexity O(1)
     */
    T Front() const;

    /**
     * @brief Checks if the queue is empty.
     * @complexity O(1)
     */
    bool IsEmpty() const { return m_list.IsEmpty(); }

    /**
     * @brief Returns the number of elements.
     * @complexity O(1)
     */
    int Size() const { return m_list.GetLength(); }

    /**
     * @brief Displays all elements in descending order.
     * @complexity O(n)
     */
    bool Display() { return m_list.Display(); }
};

// include implementation
#include "SDecendingPriorityQT.tpp"
