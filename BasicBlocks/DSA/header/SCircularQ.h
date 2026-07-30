/**
 * @file SCircularQ.h
 * @brief Declares the fixed-capacity SCircularQ class for an integer circular FIFO queue in the DSA library.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @def QUEUE_MAX
 * @brief Maximum static capacity limit for the SCircularQ internal storage buffer.
 */
#define QUEUE_MAX 255

/**
 * @class SCircularQ
 * @brief Implements a fixed-size circular FIFO (First-In-First-Out) queue using a static integer array.
 * 
 * Exported via `DSA_API` for dynamic library usage. Manages fixed-capacity element storage 
 * with `enqueue`, `dequeue`, `front`, and boundary state checks using modular arithmetic.
 */
class DSA_API SCircularQ 
{
private:
    int data[QUEUE_MAX]; ///< Static array buffer for holding queue elements up to QUEUE_MAX capacity.
    int frontIndex;      ///< Index referencing the front (head) element of the queue.
    int rearIndex;       ///< Index referencing the rear (tail) element of the queue.
    int count;           ///< Current number of elements in the queue.

public:
    /**
     * @brief Constructs an empty SCircularQ instance.
     *
     * Initializes indices and count to represent an empty buffer state.
     */
    SCircularQ();

    /**
     * @brief Inserts a new integer value at the rear of the queue.
     *
     * @param[in] value Integer value to append to the queue.
     * @throws std::runtime_error If the queue is full (`isFull() == true`).
     */
    void enqueue(int value);

    /**
     * @brief Removes and returns the integer value at the front of the queue.
     *
     * @return int The integer value previously residing at the front of the queue.
     * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
     */
    int dequeue();

    /**
     * @brief Accesses the integer value currently at the front of the queue without removing it.
     *
     * @return int Value of the front element.
     * @throws std::runtime_error If the queue is empty (`isEmpty() == true`).
     */
    int front() const;

    /**
     * @brief Checks whether the queue currently contains no elements.
     *
     * @return true If the queue is empty.
     * @return false Otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Checks whether the queue has reached its maximum static storage capacity (`QUEUE_MAX`).
     *
     * @return true If the internal buffer is completely full.
     * @return false Otherwise.
     */
    bool isFull() const;
};
