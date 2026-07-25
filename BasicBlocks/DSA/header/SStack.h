/***********************************************************************
* File: SStack.h
* Description: Declares the SStack class for a fixed-size stack implementation.
***********************************************************************/
#pragma once
#include "ExportMacro.h"

#define STACK_MAX 255

/***********************************************************************
* Class: SStack
*
* Purpose: Implements a fixed-size stack data structure with push, pop,
*          and query operations.
***********************************************************************/
class DSA_API SStack 
{
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
