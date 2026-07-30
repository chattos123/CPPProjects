/*
 * File: SListCircularQT.h
 * @brief Declares SListCircularQT<T> - circular list adapter built on SListT<T>.
 * Author: Soumyajit C
 * Date: 2026
 */

#pragma once

#include "ExportMacro.h"
#include "SListT.h"
#include <stdexcept>
#include <utility>

/**
 * @class SListCircularQT
 * @brief Circular-list adapter that reuses SListT<T> as underlying storage.
 *
 * This class provides circular semantics (rotate, push/pop at both ends)
 * while delegating node allocation and lifetime to SListT<T>. It does not
 * change SListT node pointers to be circular; instead operations like
 * Rotate() are implemented by moving elements (pop front + push back).
 *
 * @tparam T Element type stored in the list.
 */
template <typename T>
class SListCircularQT 
{
private:
    SListT<T> m_list; ///< Underlying singly-linked list that owns nodes.

    /**
     * @brief Helper: get pointer to head node (may be nullptr).
     * @return psNodeT<T> pointer to head node.
     */
    psNodeT<T> HeadNode() const { return m_list.GetHead(); }

public:
    /**
     * @brief Constructs an empty circular list adapter.
     */
    SListCircularQT() = default;

    /**
     * @brief Destructor; underlying SListT destructor frees nodes.
     */
    ~SListCircularQT() = default;

    /**
     * @brief Copy constructor (delegates to SListT copy).
     */
    SListCircularQT(const SListCircularQT& other) = default;

    /**
     * @brief Copy assignment (delegates to SListT assignment).
     */
    SListCircularQT& operator=(const SListCircularQT& other) = default;

    /**
     * @brief Move constructor (delegates to SListT move).
     */
    SListCircularQT(SListCircularQT&& other) noexcept = default;

    /**
     * @brief Move assignment (delegates to SListT move).
     */
    SListCircularQT& operator=(SListCircularQT&& other) noexcept = default;

    /**
     * @brief Append a copy of val to the logical tail.
     * @param val Value to append.
     * @return true on success; false on allocation failure.
     */
    bool PushBack(const T& val);

    /**
     * @brief Append a moved value to the logical tail.
     * @param val Rvalue reference to value to append.
     * @return true on success; false on allocation failure.
     */
    bool PushBack(T&& val);

    /**
     * @brief Insert a copy of val at the logical head.
     * @param val Value to insert at head.
     * @return true on success; false on allocation failure.
     */
    bool PushFront(const T& val);

    /**
     * @brief Insert a moved value at the logical head.
     * @param val Rvalue reference to value to insert at head.
     * @return true on success; false on allocation failure.
     */
    bool PushFront(T&& val);

    /**
     * @brief Remove and return the element at the logical head.
     * @throws std::out_of_range if the list is empty.
     * @return The removed element (moved).
     */
    T PopFront();

    /**
     * @brief Rotate the list by one element: head becomes new tail.
     *
     * Implemented as PopFront() followed by PushBack() when size > 1.
     * No-op for size 0 or 1.
     */
    void Rotate();

    /**
     * @brief Check whether the list contains a value equal to val.
     * @param val Value to search for.
     * @return true if found; false otherwise.
     */
    bool Contains(const T& val) const;

    /**
     * @brief Return number of elements.
     */
    int Size() const { return m_list.GetLength(); }

    /**
     * @brief Return true if empty.
     */
    bool IsEmpty() const { return m_list.IsEmpty(); }

    /**
     * @brief Clear all elements.
     */
    void ClearAll() noexcept { m_list = SListT<T>(); }

    // ---------------- Iterator types ----------------
    class iterator {
        psNodeT<T> m_cur;
        int m_traversed;
        int m_total;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = int;
        using pointer           = T*;
        using reference         = T&;

        iterator(psNodeT<T> cur = nullptr, int traversed = 0, int total = 0)
            : m_cur(cur), m_traversed(traversed), m_total(total) {}

        reference operator*() const { return m_cur->m_val; }
        pointer operator->() const { return &m_cur->m_val; }

        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& o) const;
        bool operator!=(const iterator& o) const;
    };

    class const_iterator {
        psNodeT<T> m_cur;
        int m_traversed;
        int m_total;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = int;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator(psNodeT<T> cur = nullptr, int traversed = 0, int total = 0)
            : m_cur(cur), m_traversed(traversed), m_total(total) {}

        reference operator*() const { return m_cur->m_val; }
        pointer operator->() const { return &m_cur->m_val; }

        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator& o) const;
        bool operator!=(const const_iterator& o) const;
    };

    /**
     * @brief Iterator to first element (head) or end() if empty.
     */
    iterator begin() { 
        psNodeT<T> h = HeadNode();
        return IsEmpty() ? iterator(nullptr, 0, 0) : iterator(h, 0, Size());
    }

    /**
     * @brief Past-the-end iterator.
     */
    iterator end() { return iterator(nullptr, Size(), Size()); }

    /**
     * @brief Const begin.
     */
    const_iterator begin() const {
        psNodeT<T> h = HeadNode();
        return IsEmpty() ? const_iterator(nullptr, 0, 0) : const_iterator(h, 0, Size());
    }

    /**
     * @brief Const end.
     */
    const_iterator end() const { return const_iterator(nullptr, Size(), Size()); }
};

// include implementation
#include "SListCircularQT.tpp"