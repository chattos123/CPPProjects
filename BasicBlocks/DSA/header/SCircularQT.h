/**
 * @file SCircularQT.h
 * @brief Declares the generic SCircularQT template class for a fixed-size circular FIFO queue.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @def QUEUE_MAX
 * @brief Maximum static capacity limit for the SCircularQT internal storage buffer.
 */
#define QUEUE_MAX 255

/**
 * @class SCircularQT
 * @brief A generic fixed-size circular FIFO (First-In-First-Out) queue template class.
 * 
 * Provides type-safe queue operations including enqueue, dequeue, front element access,
 * and boundary state queries using a fixed-capacity static array buffer with wrap-around indexing.
 *
 * @tparam T Type of elements stored within the queue.
 */
template <typename T>
class SCircularQT 
{
private:
    T data[QUEUE_MAX];  ///< Internal static array buffer holding queue elements up to QUEUE_MAX capacity.
    int frontIndex;     ///< Index referencing the front (head) element of the queue.
    int rearIndex;      ///< Index referencing the rear (tail) element of the queue.
    int count;          ///< Total number of active elements currently stored in the queue.

public:
    /**
     * @brief Constructs an empty SCircularQT instance.
     * 
     * Initializes indices and count to establish an empty buffer state.
     */
    SCircularQT() : frontIndex(0), rearIndex(-1), count(0) {}

    /**
     * @brief Default destructor for SCircularQT.
     */
    ~SCircularQT() = default;


    SCircularQT(const SCircularQT& other);  ///< Copy constructor
    SCircularQT& operator=(const SCircularQT& other); ///< Copy assignment operator
    SCircularQT(SCircularQT&& other) noexcept;        ///< Move constructor
    SCircularQT& operator=(SCircularQT&& other) noexcept; ///< Move assignment operator

    /**
     * @brief Inserts a new element at the rear of the queue.
     *
     * @param[in] value Constant reference to the element value to enqueue.
     * @throws std::runtime_error If the queue is full (`isFull() == true`).
     * @remark Wrap-around indexing ensures efficient reuse of buffer space.
     */
    void enqueue(const T& value);

    /**
     * @brief Removes and returns the element at the front of the queue.
     *
     * @return T The element value previously residing at the front of the queue.
     * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
     * @remark Advances `frontIndex` using modular arithmetic.
     */
    T dequeue();

    /**
     * @brief Accesses the element currently at the front of the queue without removing it.
     *
     * @return T Value of the front element.
     * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
     */
    T front() const;

    /**
     * @brief Checks whether the queue currently contains no elements.
     *
     * @return true If `count == 0`.
     * @return false Otherwise.
     */
    bool isEmpty() const { return count == 0; }

    /**
     * @brief Checks whether the queue has reached its maximum static array boundary limit.
     *
     * @return true If `count == QUEUE_MAX`.
     * @return false Otherwise.
     */
    bool isFull() const { return count == QUEUE_MAX; }

    //Iterators
    class iterator 
    {
    private:
        SCircularQT<T>* queue;
        int index;
        int traversed;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = int;
        using pointer           = T*;
        using reference         = T&;

        iterator(SCircularQT<T>* q, int startIndex, int traversedCount)
            : queue(q), index(startIndex), traversed(traversedCount) {}

        reference operator*() { return queue->data[index]; }
        pointer operator->() { return &queue->data[index]; }

        iterator& operator++() 
        {
            index = (index + 1) % QUEUE_MAX;
            ++traversed;
            return *this;
        }

        bool operator==(const iterator& other) const 
        {
            return queue == other.queue && traversed == other.traversed;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    iterator begin() { return iterator(this, frontIndex, 0); }
    iterator end()   { return iterator(this, (frontIndex + count) % QUEUE_MAX, count); }
};

// Include template implementation definitions
#include "SCircularQT.tpp"