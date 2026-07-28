/**
 * @file SQueue.h
 * @brief Declares the fixed-capacity SQueue class for an integer FIFO queue in the DSA library.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @def QUEUE_MAX
 * @brief Maximum static capacity limit for the SQueue internal storage buffer.
 */
#define QUEUE_MAX 255

/**
 * @class SQueue
 * @brief Implements a fixed-size FIFO (First-In-First-Out) queue using a static integer array.
 * 
 * Exported via `DSA_API` for dynamic library usage. Manages fixed-capacity element storage 
 * with `enqueue`, `dequeue`, `front`, and boundary state checks.
 */
class DSA_API SQueue {
private:
    int data[QUEUE_MAX]; ///< Static array buffer for holding queue elements up to QUEUE_MAX capacity.
    int frontIndex;      ///< Index referencing the front (head) element of the queue.
    int rearIndex;       ///< Index referencing the rear (tail) element of the queue.

public:
    /**
     * @brief Constructs an empty SQueue instance.
     * 
     * Initializes internal front and rear indices to establish an empty buffer state.
     *
     * @param None
     * @return None
     */
    SQueue();

    /**
     * @brief Inserts a new integer value at the rear of the queue.
     *
     * @param[in] value Integer value to append to the queue.
     * @return void
     * @throws std::overflow_error or std::out_of_range if invoked when the queue is full (`isFull() == true`).
     * @remark Advances the rear index reference upon successful insertion.
     */
    void enqueue(int value);

    /**
     * @brief Removes and returns the integer value at the front of the queue.
     *
     * @param None
     * @return int The integer value previously residing at the front of the queue.
     * @throws std::underflow_error or std::out_of_range if invoked when the queue is empty (`isEmpty() == true`).
     * @remark Advances the front index reference upon successful removal.
     */
    int dequeue();

    /**
     * @brief Accesses the integer value currently at the front of the queue without removing it.
     *
     * @param None
     * @return int Value of the front element.
     * @throws std::underflow_error or std::out_of_range if invoked when the queue is empty (`isEmpty() == true`).
     * @remark Non-destructive inspection method.
     */
    int front() const;

    /**
     * @brief Checks whether the queue currently contains no elements.
     *
     * @param None
     * @return true If the queue is empty.
     * @return false If the queue contains one or more elements.
     * @remark Query method providing O(1) time complexity.
     */
    bool isEmpty() const;

    /**
     * @brief Checks whether the queue has reached its maximum static storage capacity (`QUEUE_MAX`).
     *
     * @param None
     * @return true If the internal buffer is completely full.
     * @return false If space remains available for additional element insertions.
     * @remark Query method providing O(1) time complexity.
     */
    bool isFull() const;
};