/***********************************************************************
* File: SStack.cpp
* Description: Implements the SStack fixed-size stack class for the DSA library.
***********************************************************************/
#include "SStack.h"
#include <stdexcept>

/***********************************************************************/
/// <b>Function: SStack</b>
///
/// <b>remarks</b>    Initializes the stack to an empty state.
///
/***********************************************************************/
SStack::SStack() : topIndex(-1) {}

/***********************************************************************/
/// <b>Function: push</b>
///
/// <b>brief</b>      Pushes a value onto the stack.
///
/// <b>throws</b>     std::runtime_error when the stack is full.
///
/***********************************************************************/
void SStack::push(int value) {
    if (isFull())
        throw std::runtime_error("Stack overflow");
    data[++topIndex] = value;
}

/***********************************************************************/
/// <b>Function: pop</b>
///
/// <b>brief</b>      Pops and returns the top value from the stack.
///
/// <b>throws</b>     std::runtime_error when the stack is empty.
///
/***********************************************************************/
int SStack::pop() {
    if (isEmpty())
        throw std::runtime_error("Stack underflow");
    return data[topIndex--];
}

/***********************************************************************/
/// <b>Function: top</b>
///
/// <b>brief</b>      Returns the current top value without removing it.
///
/// <b>throws</b>     std::runtime_error when the stack is empty.
///
/***********************************************************************/
int SStack::top() const {
    if (isEmpty())
        throw std::runtime_error("Stack is empty");
    return data[topIndex];
}

/***********************************************************************/
/// <b>Function: isEmpty</b>
///
/// <b>brief</b>      Checks whether the stack contains any elements.
///
/// <b>return</b>     bool True if the stack is empty.
///
/***********************************************************************/
bool SStack::isEmpty() const {
    return topIndex < 0;
}

/***********************************************************************/
/// <b>Function: isFull</b>
///
/// <b>brief</b>      Checks whether the stack is at maximum capacity.
///
/// <b>return</b>     bool True if the stack is full.
///
/***********************************************************************/
bool SStack::isFull() const {
    return topIndex >= STACK_MAX - 1;
}
