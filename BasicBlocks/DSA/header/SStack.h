/***********************************************************************
* File: SStack.h
* Description: Declares the SStack class for a fixed-size stack implementation.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#define STACK_MAX 255

/***********************************************************************
* Class: SStack
*
* Purpose: Implements a fixed-size stack data structure with push, pop,
*          and query operations.
***********************************************************************/
class DSALIB_API SStack {
private:
    int data[STACK_MAX];
    int topIndex;

public:
    SStack();

    void push(int value);
    int pop();
    int top() const;
    bool isEmpty() const;
    bool isFull() const;
};
