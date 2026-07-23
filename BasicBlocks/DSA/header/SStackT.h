/***********************************************************************
* File: SStackT.h
* Description: Declares the generic SStackT template class for a type-safe stack in the DSA library.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <stdexcept>

/***********************************************************************
* Class: SStackT<T>
*
* Purpose: A generic fixed-size stack implementation supporting push, pop, 
*          and query operations with type safety.   
***********************************************************************/

template <typename T>
class DSALIB_API SStackT 
{
    private:
    T data[255];
    int topIndex;

    public:
    SStackT() : topIndex(-1) {}
    ~SStackT() = default;
    // Copy constructor
    SStackT(const SStackT& other);

    // Assignment operator
    SStackT& operator=(const SStackT& other);
    

    void push(const T& value) {
        if (topIndex >= 254) {
            throw std::runtime_error("Stack overflow");
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (topIndex < 0) {
            throw std::runtime_error("Stack underflow");
        }
        return data[topIndex--];
    }

    bool isEmpty() const {
        return topIndex < 0;
    }

    bool isFull() const {
        return topIndex >= 254;
    }

    T top() const {
        if (topIndex < 0) {
            throw std::runtime_error("Stack is empty");
        }
        return data[topIndex];
    }

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

// include template implementation
#include "SStackT.tpp"
