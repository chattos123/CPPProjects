/***********************************************************************
* File: SVectorT.tpp
* Description: Implements the templated SVectorT member functions.
***********************************************************************/

/***********************************************************************
* File: SVectorT.tpp
* Description: Implements the templated SVectorT member functions.
***********************************************************************/

template <typename T>
/***********************************************************************/
/// <b>Function: SVectorT</b>
///
/// \remarks    Default constructor initializes an empty templated vector.
///
/***********************************************************************/
SVectorT<T>::SVectorT() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
/***********************************************************************/
/// <b>Function: ~SVectorT</b>
///
/// \remarks    Destructor frees allocated array storage.
///
/***********************************************************************/
SVectorT<T>::~SVectorT() {
    delete[] m_data;
    m_data = nullptr; // avoid dangling pointer
}

template <typename T>
/***********************************************************************/
/// <b>Function: SVectorT</b>
///
/// \brief      Copy constructor performs a deep copy of the source vector.
///
/***********************************************************************/
SVectorT<T>::SVectorT(const SVectorT& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

template <typename T>
/***********************************************************************/
/// <b>Function: SVectorT</b>
///
/// \brief      Move constructor transfers ownership of resources from source.
///
/***********************************************************************/
SVectorT<T>::SVectorT(SVectorT&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    // Steal resources
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}


template <typename T>
/***********************************************************************/
/// <b>Function: operator=</b>
///
/// \brief      Copy assignment performs a deep copy of the source vector.
///
/***********************************************************************/
SVectorT<T>& SVectorT<T>::operator=(const SVectorT& other) {
    if (this == &other) return *this;

    delete[] m_data;

    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

template <typename T>
/***********************************************************************/
/// <b>Function: operator+</b>
///
/// \brief      Returns a new vector that concatenates this vector with another.
///
/***********************************************************************/
SVectorT<T> SVectorT<T>::operator+(const SVectorT& other) const {
    SVectorT<T> result;
    result.reserve(m_size + other.m_size);

    for (int i = 0; i < m_size; ++i) result.push_back(m_data[i]);
    for (int i = 0; i < other.m_size; ++i) result.push_back(other.m_data[i]);

    return result;
}

template <typename T>
/***********************************************************************/
/// <b>Function: resize</b>
///
/// \brief      Resizes the internal storage capacity of the vector.
///
/***********************************************************************/
void SVectorT<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < m_size; ++i) {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

template <typename T>
/***********************************************************************/
/// <b>Function: push_back</b>
///
/// \brief      Appends a value to the end of the vector.
///
/***********************************************************************/
void SVectorT<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        resize(newCapacity);
    }
    m_data[m_size++] = value;
}

template <typename T>
/***********************************************************************/
/// <b>Function: pop_back</b>
///
/// \brief      Removes the last element from the vector.
///
/***********************************************************************/
void SVectorT<T>::pop_back() {
    if (m_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --m_size;
}

template <typename T>
/***********************************************************************/
/// <b>Function: at</b>
///
/// \brief      Returns the element at the specified index with bounds checking.
///
/***********************************************************************/
T SVectorT<T>::at(int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template <typename T>
/***********************************************************************/
/// <b>Function: operator[]</b>
///
/// \brief      Returns a mutable reference to the element at index.
///
/***********************************************************************/
T& SVectorT<T>::operator[](int index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template <typename T>
/***********************************************************************/
/// <b>Function: operator[]</b>
///
/// \brief      Returns a const reference to the element at index.
///
/***********************************************************************/
const T& SVectorT<T>::operator[](int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

template <typename T>
/***********************************************************************/
/// <b>Function: operator=</b>
///
/// \brief      Move assignment transfers ownership from the source vector.
///
/***********************************************************************/
SVectorT<T>& SVectorT<T>::operator=(SVectorT&& other) noexcept {
    if (this == &other) return *this; // self-assignment check

    // Free current resources
    delete[] m_data;

    // Steal resources
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    // Reset source
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;

    return *this;
}


template <typename T>
/***********************************************************************/
/// <b>Function: reserve</b>
///
/// \brief      Reserves storage capacity for at least newCapacity elements.
///
/***********************************************************************/
void SVectorT<T>::reserve(int newCapacity) {
    if (newCapacity > m_capacity) {
        resize(newCapacity);
    }
}

template <typename T>
/***********************************************************************/
/// <b>Function: resizeSize</b>
///
/// \brief      Changes the logical size of the vector.
///
/***********************************************************************/
void SVectorT<T>::resizeSize(int newSize) {
    if (newSize > m_capacity) {
        resize(newSize);
    }
    m_size = newSize;
}

template <typename T>
/***********************************************************************/
/// <b>Function: display</b>
///
/// \brief      Prints the contents of the vector to standard output.
///
/***********************************************************************/
void SVectorT<T>::display() const {
    std::cout << "[ ";
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_data[i] << " ";
    }
    std::cout << "]\n";
}
