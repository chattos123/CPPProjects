/**
 * @file SStack.cpp
 * @brief Implementation of the fixed-capacity SStack class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SStack.h"
#include <stdexcept>

/**
 * @brief Constructs an empty SStack instance.
 *
 * Initializes `topIndex` to -1 to represent an empty static array buffer.
 *
 * @param None
 */
SStack::SStack() : topIndex(-1) {}

/**
 * @brief Pushes a new integer value onto the top of the stack.
 *
 * Increments `topIndex` and stores the value in the static array buffer.
 *
 * @param[in] value Integer value to push onto the stack.
 * @return void
 * @throws std::runtime_error If the stack is full (`isFull() == true`).
 * @remark Operates with O(1) time complexity.
 */
void SStack::push(int value) 
{
    if (isFull())
        throw std::runtime_error("Stack overflow");
    data[++topIndex] = value;
}

/**
 * @brief Removes and returns the integer value at the top of the stack.
 *
 * Retrieves the element at `topIndex` and decrements the top index pointer.
 *
 * @param None
 * @return int The integer value previously residing at the top of the stack.
 * @throws std::runtime_error If the stack is empty (`isEmpty() == true`).
 * @remark Operates with O(1) time complexity.
 */
int SStack::pop() 
{
    if (isEmpty())
        throw std::runtime_error("Stack underflow");
    return data[topIndex--];
}

/**
 * @brief Accesses the integer value currently at the top of the stack without removing it.
 *
 * @param None
 * @return int Value of the top element.
 * @throws std::runtime_error If the stack is empty (`isEmpty() == true`).
 * @remark Non-destructive inspection method providing O(1) time complexity.
 */
int SStack::top() const 
{
    if (isEmpty())
        throw std::runtime_error("Stack is empty");
    return data[topIndex];
}

/**
 * @brief Checks whether the stack currently contains no elements.
 *
 * @param None
 * @return true If `topIndex < 0`.
 * @return false If active elements remain in the stack.
 * @remark Query method providing O(1) time complexity.
 */
bool SStack::isEmpty() const 
{
    return topIndex < 0;
}

/**
 * @brief Checks whether the stack has reached its maximum static storage capacity (`STACK_MAX`).
 *
 * @param None
 * @return true If `topIndex >= STACK_MAX - 1`.
 * @return false If buffer space remains available for additional element pushes.
 * @remark Query method providing O(1) time complexity.
 */
bool SStack::isFull() const 
{
    return topIndex >= STACK_MAX - 1;
}