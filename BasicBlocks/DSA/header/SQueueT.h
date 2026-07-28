/**
 * @file SQueueT.h
 * @brief Declares the generic SQueueT template class for a fixed-size non-circular FIFO queue.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @def QUEUE_MAX
 * @brief Maximum static capacity limit for the SQueueT internal storage buffer.
 */
#define QUEUE_MAX 255

/**
 * @class SQueueT
 * @brief A generic fixed-size non-circular FIFO (First-In-First-Out) queue template class.
 * 
 * Provides type-safe queue operations including enqueue, dequeue, front element access,
 * and boundary state queries using a fixed-capacity static array buffer.
 *
 * @tparam T Type of elements stored within the queue.
 */
template <typename T>
class SQueueT {
private:
    T data[QUEUE_MAX];  ///< Internal static array buffer holding queue elements up to QUEUE_MAX capacity.
    int frontIndex;     ///< Index referencing the front (head) element of the queue.
    int count;          ///< Total number of active elements currently stored in the queue.

public:
    /**
     * @brief Constructs an empty SQueueT instance.
     * 
     * Initializes `frontIndex` to 0 and `count` to 0 to establish an empty buffer state.
     *
     * @param None
     */
    SQueueT() : frontIndex(0), count(0) {}

    /**
     * @brief Default destructor for SQueueT.
     */
    ~SQueueT() = default;

    /**
     * @brief Inserts a new element at the rear of the queue.
     *
     * @param[in] value Constant reference to the element value to enqueue.
     * @return void
     * @throws std::overflow_error or std::runtime_error if invoked when the queue is full (`isFull() == true`).
     * @remark Increments internal element count upon successful insertion.
     */
    void enqueue(const T& value);

    /**
     * @brief Removes and returns the element at the front of the queue.
     *
     * @param None
     * @return T The element value previously residing at the front of the queue.
     * @throws std::underflow_error or std::runtime_error if invoked when the queue is empty (`isEmpty() == true`).
     * @remark Advances `frontIndex` and decrements internal element `count`.
     */
    T dequeue();

    /**
     * @brief Accesses the element currently at the front of the queue without removing it.
     *
     * @param None
     * @return T Value of the front element.
     * @throws std::underflow_error or std::runtime_error if invoked when the queue is empty (`isEmpty() == true`).
     * @remark Non-destructive inspection method.
     */
    T front() const;

    /**
     * @brief Checks whether the queue currently contains no elements.
     *
     * @param None
     * @return true If `count == 0`.
     * @return false If the queue contains one or more elements.
     * @remark Inline query method providing O(1) time complexity.
     */
    bool isEmpty() const { return count == 0; }

    /**
     * @brief Checks whether the queue has reached its maximum static array boundary limit.
     *
     * @param None
     * @return true If `(frontIndex + count) >= QUEUE_MAX`.
     * @return false If space remains available at the rear for additional enqueues.
     * @remark Inline query method providing O(1) time complexity.
     */
    bool isFull() const { return (frontIndex + count) >= QUEUE_MAX; }
};

// Include template implementation definitions
#include "SQueueT.tpp"