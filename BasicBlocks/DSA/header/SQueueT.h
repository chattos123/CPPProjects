/***********************************************************************
* File: SQueueT.h
* Description: Declares the generic SQueueT template class for a 
*              fixed-size non-circular queue implementation.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#define QUEUE_MAX 255

/***********************************************************************
* Class: SQueueT<T>
*
* Purpose: Implements a fixed-size non-circular queue data structure 
*          with enqueue, dequeue, and query operations.
***********************************************************************/
template <typename T>
class DSALIB_API SQueueT {
private:
    T data[QUEUE_MAX];
    int frontIndex;
    int count;

public:
    SQueueT() : frontIndex(0), count(0) {}
    ~SQueueT() = default;

    void enqueue(const T& value);
    T dequeue();
    T front() const;

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return (frontIndex + count) >= QUEUE_MAX; }
};

#include "SQueueT.tpp"
