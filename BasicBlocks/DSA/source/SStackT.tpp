template <typename T>
SStackT<T>::SStackT(const SStackT& other) {
    topIndex = other.topIndex;
    for (int i = 0; i <= topIndex; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
SStackT<T>& SStackT<T>::operator=(const SStackT& other) {
    if (this == &other) return *this; // self-assignment check

    topIndex = other.topIndex;
    for (int i = 0; i <= topIndex; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

