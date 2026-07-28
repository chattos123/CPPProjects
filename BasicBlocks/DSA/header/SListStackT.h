/**
 * @file SListStackT.h
 * @brief Declares the generic SListStackT template class for a type-safe LIFO stack built on SListT.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"
#include "SListT.h"
#include <stdexcept>
#include <iostream>

/**
 * @class SListStackT
 * @brief A generic LIFO (Last-In-First-Out) stack container adapter built on top of the SListT template class.
 * 
 * Provides standard stack primitives including push, pop, top, and capacity queries with full type safety.
 *
 * @tparam T Type of elements stored within the stack container.
 */
template <typename T>
class SListStackT 
{
private:
    SListT<T> m_list; ///< Underlying singly-linked list container holding stack elements.

public:
    /**
     * @brief Constructs an empty SListStackT instance.
     */
    SListStackT() = default;

    /**
     * @brief Destructs the SListStackT instance and releases underlying container memory.
     */
    ~SListStackT() = default;

    /**
     * @brief Copy constructor for performing a deep copy of another SListStackT instance.
     *
     * @param[in] other Source stack instance to duplicate.
     */
    SListStackT(const SListStackT& other);

    /**
     * @brief Copy assignment operator for assigning another SListStackT instance to this stack.
     *
     * @param[in] other Source stack instance to assign.
     * @return SListStackT& Reference to this updated stack instance.
     * @remark Handles self-assignment checks internally.
     */
    SListStackT& operator=(const SListStackT& other);

    /**
     * @brief Pushes a new element onto the top of the stack.
     *
     * @param[in] value Reference to the element value to insert onto the stack.
     * @return void
     * @remark Delegates element insertion to the underlying SListT container.
     */
    void push(const T& value);

    /**
     * @brief Removes and returns the element at the top of the stack.
     *
     * @param None
     * @return T The element value previously residing at the top of the stack.
     * @throws std::underflow_error or std::out_of_range if invoked on an empty stack.
     * @remark Modifies the stack by reducing its size by one.
     */
    T pop();

    /**
     * @brief Accesses the element currently residing at the top of the stack without removing it.
     *
     * @param None
     * @return T Value of the top element.
     * @throws std::underflow_error or std::out_of_range if invoked on an empty stack.
     * @remark Non-destructive inspection method.
     */
    T top() const;

    /**
     * @brief Checks whether the stack contains any elements.
     *
     * @param None
     * @return true If the stack is empty.
     * @return false If the stack contains one or more elements.
     * @remark Inline query delegating directly to m_list.IsEmpty().
     */
    bool isEmpty() const { return m_list.IsEmpty(); }

    /**
     * @brief Retrieves the current number of elements held within the stack.
     *
     * @param None
     * @return int Total number of stored elements.
     * @remark Inline query delegating directly to m_list.GetLength().
     */
    int size() const { return m_list.GetLength(); }

    /**
     * @brief Displays the current contents of the stack to standard output.
     *
     * @param None
     * @return void
     * @remark Non-destructive traversal output.
     */
    void display() const;
};

// Include template implementation definitions
#include "SListStackT.tpp"