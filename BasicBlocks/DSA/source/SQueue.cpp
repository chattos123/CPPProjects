#include "SQueue.h"
#include <stdexcept>

SQueue::SQueue() : frontIndex(0), rearIndex(-1) {}

void SQueue::enqueue(int value) {
    if (isFull()) {
        throw std::runtime_error("Queue overflow");
    }
    data[++rearIndex] = value;
}

int SQueue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue underflow");
    }
    int value = data[frontIndex++];
    return value;
}

int SQueue::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[frontIndex];
}

bool SQueue::isEmpty() const {
    return frontIndex > rearIndex;
}

bool SQueue::isFull() const {
    return rearIndex == QUEUE_MAX - 1;
}
