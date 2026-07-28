/**
 * @file SStackT.h
 * @brief Declares the generic SStackT template class for a fixed-size, type-safe LIFO stack.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

#include <iostream>
#include <stdexcept>

/**
 * @class SStackT
 * @brief A generic fixed-size LIFO (Last-In-First-Out) stack implementation holding up to 255 elements.
 * 
 * Supports standard stack operations including push, pop, top, boundary queries, copy construction, 
 * copy assignment, and stream output with complete type safety.
 *
 * @tparam T Type of elements stored within the stack.
 */
template <typename T>
class SStackT 
{
private:
    T data[255];  ///< Internal array buffer holding stack elements up to capacity 255.
    int topIndex; ///< Index referencing the current top element (-1 when empty).

public:
    /**
     * @brief Constructs an empty SStackT instance.
     * 
     * Initializes `topIndex` to -1 to represent an empty stack buffer.
     *
     * @param None
     */
    SStackT() : topIndex(-1) {}

    /**
     * @brief Default destructor for SStackT.
     */
    ~SStackT() = default;

    /**
     * @brief Copy constructor performing a deep copy of another SStackT instance.
     *
     * @param[in] other Source `SStackT` instance to copy from.
     */
    SStackT(const SStackT& other);

    /**
     * @brief Copy assignment operator for assigning another SStackT instance.
     *
     * @param[in] other Source `SStackT` instance to copy.
     * @return SStackT& Reference to this updated `SStackT` instance.
     * @remark Protects against self-assignment.
     */
    SStackT& operator=(const SStackT& other);

    /**
     * @brief Pushes a new element onto the top of the stack.
     *
     * @param[in] value Constant reference to the element value to push.
     * @return void
     * @throws std::runtime_error If invoked when the stack is full (`topIndex >= 254`).
     * @remark Increments `topIndex` upon successful insertion.
     */
    void push(const T& value) {
        if (topIndex >= 254) {
            throw std::runtime_error("Stack overflow");
        }
        data[++topIndex] = value;
    }

    /**
     * @brief Removes and returns the element at the top of the stack.
     *
     * @param None
     * @return T The element value previously residing at the top of the stack.
     * @throws std::runtime_error If invoked on an empty stack (`topIndex < 0`).
     * @remark Decrements `topIndex` upon successful removal.
     */
    T pop() {
        if (topIndex < 0) {
            throw std::runtime_error("Stack underflow");
        }
        return data[topIndex--];
    }

    /**
     * @brief Checks whether the stack currently contains no elements.
     *
     * @param None
     * @return true If `topIndex < 0`.
     * @return false If the stack contains one or more elements.
     * @remark Inline query providing O(1) time complexity.
     */
    bool isEmpty() const {
        return topIndex < 0;
    }

    /**
     * @brief Checks whether the stack has reached its maximum static storage capacity (255 elements).
     *
     * @param None
     * @return true If `topIndex >= 254`.
     * @return false If capacity remains available for additional pushes.
     * @remark Inline query providing O(1) time complexity.
     */
    bool isFull() const {
        return topIndex >= 254;
    }

    /**
     * @brief Accesses the element currently at the top of the stack without removing it.
     *
     * @param None
     * @return T Value of the element at the top of the stack.
     * @throws std::runtime_error If invoked on an empty stack (`topIndex < 0`).
     * @remark Non-destructive inspection method.
     */
    T top() const {
        if (topIndex < 0) {
            throw std::runtime_error("Stack is empty");
        }
        return data[topIndex];
    }

    /**
     * @brief Displays the current contents of the stack from top to bottom to standard output.
     *
     * @param None
     * @return void
     * @remark Non-destructive traversal. Requires `operator<<` to be defined for type T.
     */
    void display() const 
    {
        if (isEmpty()) {
            std::cout << "Stack is empty\n";
            return;
        }
        std::cout << "Stack contents (top to bottom):\n";
        for (int i = topIndex; i >= 0; --i) {
            std::cout << data[i] << "\n";
        }
    }
};

// Include template implementation definitions
#include "SStackT.tpp"