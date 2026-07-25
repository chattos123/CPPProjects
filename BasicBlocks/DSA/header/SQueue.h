#pragma once
#include "ExportMacro.h"

#define QUEUE_MAX 255

class DSA_API SQueue {
private:
    int data[QUEUE_MAX];
    int frontIndex;
    int rearIndex;

public:
    SQueue();

    void enqueue(int value);
    int dequeue();
    int front() const;
    bool isEmpty() const;
    bool isFull() const;
};
