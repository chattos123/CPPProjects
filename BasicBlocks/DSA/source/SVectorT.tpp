/**
 * @file SVectorT.tpp
 * @brief Implementation of the templated dynamic array class (`SVectorT`).
 * @details Contains template member function definitions for dynamic resizing, 
 *          memory reservation, deep copying, move semantics, element access, 
 *          and sequence concatenation.
 * 
 * @author Soumyajit C
 * @date 2026
 */

// ============================================================================
// Constructors & Destructor
// ============================================================================

/**
 * @brief Default constructor. Initializes an empty templated vector.
 *
 * @tparam T Data type of the elements stored in the vector.
 */
template <typename T>
SVectorT<T>::SVectorT() : m_data(nullptr), m_size(0), m_capacity(0) {}

/**
 * @brief Destructor. Deallocates the dynamic array storage.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @note Frees `m_data` using `delete[]` and sets the pointer to `nullptr`.
 */
template <typename T>
SVectorT<T>::~SVectorT() 
{
    delete[] m_data;
    m_data = nullptr;
}

/**
 * @brief Copy constructor. Performs a deep copy of the source vector.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] other Const reference to the source `SVectorT` instance to copy.
 */
template <typename T>
SVectorT<T>::SVectorT(const SVectorT& other) 
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];

    for (int i = 0; i < m_size; ++i) 
    {
        m_data[i] = other.m_data[i];
    }
}

/**
 * @brief Move constructor. Transfers ownership of resources from the source vector.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in,out] other Rvalue reference to the source `SVectorT` object.
 *
 * @note Resets `other` to an empty state (`m_data = nullptr`, `m_size = 0`, `m_capacity = 0`).
 */
template <typename T>
SVectorT<T>::SVectorT(SVectorT&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) 
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

// ============================================================================
// Assignment Operators
// ============================================================================

/**
 * @brief Deep copy assignment operator.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] other Const reference to the source `SVectorT` object to copy.
 * @return SVectorT<T>& Reference to `*this`.
 *
 * @note Includes a self-assignment check (`this == &other`) and deallocates existing memory before copying.
 */
template <typename T>
SVectorT<T>& SVectorT<T>::operator=(const SVectorT& other) 
{
    if (this == &other) return *this;

    delete[] m_data;

    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];

    for (int i = 0; i < m_size; ++i) 
    {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

/**
 * @brief Move assignment operator.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in,out] other Rvalue reference to the source `SVectorT` object to move.
 * @return SVectorT<T>& Reference to `*this`.
 *
 * @note Includes a self-assignment check (`this == &other`), frees existing storage, 
 *       and resets source metadata.
 */
template <typename T>
SVectorT<T>& SVectorT<T>::operator=(SVectorT&& other) noexcept 
{
    if (this == &other) return *this;

    delete[] m_data;

    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;

    return *this;
}

// ============================================================================
// Capacity & Resizing Operations
// ============================================================================

/**
 * @brief Reallocates internal array storage to a new capacity.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] newCapacity Target buffer capacity in number of elements.
 */
template <typename T>
void SVectorT<T>::resize(int newCapacity) 
{
    T* newData = new T[newCapacity];

    for (int i = 0; i < m_size; ++i) 
    {
        newData[i] = m_data[i];
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

/**
 * @brief Reserves storage capacity for at least `newCapacity` elements.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] newCapacity Minimum storage capacity to reserve.
 *
 * @note Reallocates internal storage only if `newCapacity > m_capacity`.
 */
template <typename T>
void SVectorT<T>::reserve(int newCapacity) 
{
    if (newCapacity > m_capacity) 
    {
        resize(newCapacity);
    }
}

/**
 * @brief Adjusts the logical size of the vector.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] newSize Target element count for the vector.
 *
 * @note Reallocates storage if `newSize > m_capacity`.
 */
template <typename T>
void SVectorT<T>::resizeSize(int newSize) 
{
    if (newSize > m_capacity) 
    {
        resize(newSize);
    }

    m_size = newSize;
}

// ============================================================================
// Element Modification Operations
// ============================================================================

/**
 * @brief Appends an element to the end of the vector.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] value Const reference to the value to append.
 *
 * @note Automatically doubles capacity when `m_size == m_capacity`.
 */
template <typename T>
void SVectorT<T>::push_back(const T& value) 
{
    if (m_size == m_capacity) 
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        resize(newCapacity);
    }

    m_data[m_size++] = value;
}

/**
 * @brief Removes the last element from the vector.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @throws std::out_of_range Thrown if invoked when the vector is empty (`m_size == 0`).
 */
template <typename T>
void SVectorT<T>::pop_back() 
{
    if (m_size == 0) 
    {
        throw std::out_of_range("Vector is empty");
    }
    --m_size;
}

// ============================================================================
// Element Accessors & Operators
// ============================================================================

/**
 * @brief Accesses the element at the specified index with bounds checking (value copy).
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] index Zero-based element index.
 * @return T Copy of the element at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
template <typename T>
T SVectorT<T>::at(int index) const 
{
    if (index < 0 || index >= m_size) 
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

/**
 * @brief Subscript element access operator (mutable).
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] index Zero-based element index.
 * @return T& Reference to the element at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
template <typename T>
T& SVectorT<T>::operator[](int index) 
{
    if (index < 0 || index >= m_size) 
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

/**
 * @brief Subscript element access operator (read-only).
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] index Zero-based element index.
 * @return const T& Const reference to the element at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
template <typename T>
const T& SVectorT<T>::operator[](int index) const 
{
    if (index < 0 || index >= m_size) 
    {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

// ============================================================================
// Binary Operators & Utility
// ============================================================================

/**
 * @brief Binary addition operator. Concatenates two vectors into a new vector object.
 *
 * @tparam T Data type of the elements stored in the vector.
 * @param[in] other Const reference to the right-hand side `SVectorT` operand.
 * @return SVectorT<T> A new `SVectorT` instance containing concatenated elements.
 */
template <typename T>
SVectorT<T> SVectorT<T>::operator+(const SVectorT& other) const 
{
    SVectorT<T> result;
    result.reserve(m_size + other.m_size);

    for (int i = 0; i < m_size; ++i) result.push_back(m_data[i]);
    for (int i = 0; i < other.m_size; ++i) result.push_back(other.m_data[i]);

    return result;
}

/**
 * @brief Outputs vector contents to standard output stream (`std::cout`).
 *
 * @tparam T Data type of the elements stored in the vector.
 * @note Requires type `T` to support stream insertion operator (`operator<<`).
 */
template <typename T>
void SVectorT<T>::display() const 
{
    std::cout << "[ ";

    for (int i = 0; i < m_size; ++i) 
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << "]\n";
}