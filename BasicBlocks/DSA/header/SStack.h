/**
 * @file SStack.h
 * @brief Declares the fixed-capacity SStack class for an integer LIFO stack in the DSA library.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @def STACK_MAX
 * @brief Maximum static capacity limit for the SStack internal storage buffer.
 */
#define STACK_MAX 255

/**
 * @class SStack
 * @brief Implements a fixed-size LIFO (Last-In-First-Out) stack using a static integer array.
 * 
 * Exported via `DSA_API` for dynamic library usage. Manages fixed-capacity element storage 
 * with `push`, `pop`, `top`, and boundary state checks.
 */
class DSA_API SStack 
{
private:
    int data[STACK_MAX]; ///< Static array buffer for holding stack elements up to STACK_MAX capacity.
    int topIndex;        ///< Index referencing the current top element of the stack (-1 when empty).

public:
    /**
     * @brief Constructs an empty SStack instance.
     * 
     * Initializes internal `topIndex` to -1 to establish an empty buffer state.
     *
     * @param None
     * @return None
     */
    SStack();

    /**
     * @brief Pushes a new integer value onto the top of the stack.
     *
     * @param[in] value Integer value to place onto the stack.
     * @return void
     * @throws std::overflow_error or std::out_of_range if invoked when the stack is full (`isFull() == true`).
     * @remark Increments `topIndex` upon successful insertion.
     */
    void push(int value);

    /**
     * @brief Removes and returns the integer value at the top of the stack.
     *
     * @param None
     * @return int The integer value previously residing at the top of the stack.
     * @throws std::underflow_error or std::out_of_range if invoked when the stack is empty (`isEmpty() == true`).
     * @remark Decrements `topIndex` upon successful removal.
     */
    int pop();

    /**
     * @brief Accesses the integer value currently at the top of the stack without removing it.
     *
     * @param None
     * @return int Value of the top element.
     * @throws std::underflow_error or std::out_of_range if invoked when the stack is empty (`isEmpty() == true`).
     * @remark Non-destructive inspection method.
     */
    int top() const;

    /**
     * @brief Checks whether the stack currently contains no elements.
     *
     * @param None
     * @return true If `topIndex == -1`.
     * @return false If the stack contains one or more elements.
     * @remark Query method providing O(1) time complexity.
     */
    bool isEmpty() const;

    /**
     * @brief Checks whether the stack has reached its maximum static storage capacity (`STACK_MAX`).
     *
     * @param None
     * @return true If `topIndex == STACK_MAX - 1`.
     * @return false If space remains available for additional element pushes.
     * @remark Query method providing O(1) time complexity.
     */
    bool isFull() const;
};