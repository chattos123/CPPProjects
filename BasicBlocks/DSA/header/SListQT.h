/*
 * File: SListQT.h
 * @brief Adapter SListQT<T> implemented on top of SListT<T>.
 * Author: Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"
#include "SListT.h"
#include <stdexcept>

/**
 * @class SListQT
 * @brief Queue adapter built on top of SListT<T>.
 *
 * Provides queue-like semantics (FIFO) by delegating node management
 * to the underlying singly-linked list container SListT<T>.
 *
 * @tparam T Element type stored in the queue.
 */
template <typename T>
class SListQT 
{
private:
    SListT<T> m_list; ///< Underlying singly-linked list implementation.

public:
    /**
     * @brief Constructs an empty SListQT instance.
     */
    SListQT() = default;

    /**
     * @brief Default destructor; underlying SListT frees nodes.
     */
    ~SListQT() = default;

    /**
     * @brief Copy constructor (deep copy via SListT).
     * @param other Source queue to copy.
     */
    SListQT(const SListQT& other) = default;

    /**
     * @brief Copy assignment operator (deep copy via SListT).
     * @param other Source queue to assign.
     * @return Reference to this queue.
     */
    SListQT& operator=(const SListQT& other) = default;

    /**
     * @brief Move constructor (delegates to SListT move).
     * @param other Source queue to move from.
     */
    SListQT(SListQT&& other) noexcept = default;

    /**
     * @brief Move assignment operator (delegates to SListT move).
     * @param other Source queue to move from.
     * @return Reference to this queue.
     */
    SListQT& operator=(SListQT&& other) noexcept = default;

    // ---------------- Forwarded API ----------------

    /**
     * @brief Append a new element to the tail of the list.
     * @param val Value to append.
     * @return true if successful; false if allocation failed.
     */
    bool AddElement(const T& val) { return m_list.AddElement(val); }

    /**
     * @brief Insert a new element after the given position.
     * @param pos 0-based index after which to insert.
     * @param val Value to insert.
     * @return true if successful; false if out of bounds or allocation failed.
     */
    bool AddElementAfter(int pos, const T& val) { return m_list.AddElementAfter(pos, val); }

    /**
     * @brief Insert a new element at the head of the list.
     * @param val Value to insert.
     * @return true if successful; false if allocation failed.
     */
    bool AddHead(const T& val) { return m_list.AddHead(val); }

    /**
     * @brief Delete the head node.
     * @return true if successful; false if list was empty.
     */
    bool DeleteHead() { return m_list.DeleteHead(); }

    /**
     * @brief Delete the tail node.
     * @return true if successful; false if list was empty.
     */
    bool DeleteElement() { return m_list.DeleteElement(); }

    /**
     * @brief Get pointer to head node.
     * @return psNodeT<T> pointer to head node or nullptr if empty.
     */
    psNodeT<T> GetHead() const { return m_list.GetHead(); }

    /**
     * @brief Get pointer to node at index.
     * @param index 0-based index (default 0 = head).
     * @return psNodeT<T> pointer to node or nullptr if out of bounds.
     */
    psNodeT<T> GetElementAt(int index = 0) { return m_list.GetElementAt(index); }

    /**
     * @brief Get pointer to last node.
     * @return psNodeT<T> pointer to tail node or nullptr if empty.
     */
    psNodeT<T> GetLastElement() { return m_list.GetLastElement(); }

    /**
     * @brief Check if list is empty.
     * @return true if empty; false otherwise.
     */
    bool IsEmpty() const { return m_list.IsEmpty(); }

    /**
     * @brief Get number of elements.
     * @return Current length.
     */
    int GetLength() const { return m_list.GetLength(); }

    /**
     * @brief Display all elements to stdout.
     * @return true if successful; false if empty.
     */
    bool Display() { return m_list.Display(); }

    // ---------------- Queue Helpers ----------------

    /**
     * @brief Enqueue an element (append to tail).
     * @param val Value to enqueue.
     * @return true if successful; false if allocation failed.
     */
    bool Enqueue(const T& val) { return AddElement(val); }

    /**
     * @brief Dequeue an element (remove from head).
     * @throws std::out_of_range if empty.
     * @throws std::runtime_error if DeleteHead fails.
     * @return Value removed from head.
     */
    T Dequeue() {
        psNodeT<T> head = m_list.GetHead();
        if (!head) throw std::out_of_range("SListQT::Dequeue - list is empty");
        T val = head->m_val;
        if (!DeleteHead()) throw std::runtime_error("SListQT::Dequeue - failed to delete head");
        return val;
    }
};