#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#define QUEUE_MAX 255

class DSALIB_API SQueue {
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
