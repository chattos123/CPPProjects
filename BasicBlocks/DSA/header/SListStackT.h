/***********************************************************************
* File: SListStackT.h
* Description: Declares the generic SListStackT template class for a 
*              type-safe stack built on top of SListT.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include "SListT.h"
#include <stdexcept>
#include <iostream>

/***********************************************************************
* Class: SListStackT<T>
*
* Purpose: A generic stack implementation using a singly-linked list
*          as the underlying container. Provides push, pop, top, and
*          query operations with type safety.
***********************************************************************/
template <typename T>
class DSALIB_API SListStackT {
private:
    SListT<T> m_list;

public:
    SListStackT() = default;
    ~SListStackT() = default;

    // Copy constructor
    SListStackT(const SListStackT& other);

    // Assignment operator
    SListStackT& operator=(const SListStackT& other);

    void push(const T& value);
    T pop();
    T top() const;

    bool isEmpty() const { return m_list.IsEmpty(); }
    int size() const { return m_list.GetLength(); }

    void display() const;
};

// include template implementation
#include "SListStackT.tpp"
