#include <stdexcept>

template <typename T>
void SQueueT<T>::enqueue(const T& value) {
    if (isFull()) {
        throw std::runtime_error("Queue overflow");
    }
    data[frontIndex + count] = value;
    ++count;
}

template <typename T>
T SQueueT<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue underflow");
    }
    T value = data[frontIndex];
    ++frontIndex;
    --count;

    // Reset indices when queue becomes empty
    if (count == 0) {
        frontIndex = 0;
    }

    return value;
}

template <typename T>
T SQueueT<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[frontIndex];
}
