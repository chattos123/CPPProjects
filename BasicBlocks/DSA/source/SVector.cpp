/**
 * @file SVector.cpp
 * @brief Implementation of the dynamic array class (`SVector`) for the DSA library.
 * @details Handles dynamic reallocation, deep copying, move semantics, basic sequence 
 *          operations, and overloaded access/concatenation operators for integer arrays.
 * 
 * @author Soumyajit C
 * @date 2026
 */

#include <stdexcept>
#include <iostream>
#include "SVector.h"

/**
 * @def VECTOR_ATOMICITY
 * @brief Expansion growth factor used during dynamic array reallocation.
 */
#define VECTOR_ATOMICITY 2

// ============================================================================
// Constructors & Destructor
// ============================================================================

/**
 * @brief Default constructor. Constructs an empty `SVector` instance.
 *
 * @details Initializes the internal data pointer to `nullptr` and sets both length
 *          and storage capacity to zero.
 */
SVector::SVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

/**
 * @brief Copy constructor. Performs a deep copy of another `SVector` instance.
 *
 * @param[in] other Const reference to the source `SVector` instance to copy.
 *
 * @note Allocates a new heap array matching `other.m_capacity` and copies all elements.
 */
SVector::SVector(const SVector& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new int[m_capacity];

    for (int i = 0; i < m_size; ++i) 
    {
        m_data[i] = other.m_data[i];
    }
}

/**
 * @brief Move constructor. Transfers resource ownership from a temporary `SVector` instance.
 *
 * @param[in,out] other Rvalue reference to the source `SVector` object.
 *
 * @note Leaves `other` in a valid but empty state (`m_data = nullptr`, `m_size = 0`, `m_capacity = 0`).
 */
SVector::SVector(SVector&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) 
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

/**
 * @brief Destructor. Deallocates heap-allocated internal storage.
 *
 * @remark Safely frees `m_data` using `delete[]` and resets the pointer to `nullptr`.
 */
SVector::~SVector() 
{
    delete[] m_data;
    m_data = nullptr;
}

// ============================================================================
// Capacity & Storage Management
// ============================================================================

/**
 * @brief Reallocates internal storage to a new capacity.
 *
 * @param[in] newCapacity Target capacity size in elements.
 *
 * @details Allocates a new block of memory, copies existing elements up to `m_size`,
 *          frees the old buffer, and updates the internal capacity tracking variable.
 */
void SVector::resize(int newCapacity) {
    int* newData = new int[newCapacity];
    for (int i = 0; i < m_size; ++i) {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

// ============================================================================
// Element Modification Operations
// ============================================================================

/**
 * @brief Appends a new integer value to the end of the vector.
 *
 * @param[in] value Integer value to append.
 *
 * @details Automatically triggers dynamic buffer expansion using `VECTOR_ATOMICITY` 
 *          when `m_size` reaches `m_capacity`.
 */
void SVector::push_back(int value) 
{
    if (m_size == m_capacity) 
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * VECTOR_ATOMICITY;
        resize(newCapacity);
    }

    m_data[m_size++] = value;
}

/**
 * @brief Removes the last element from the vector.
 *
 * @throws std::out_of_range Thrown if invoked when the vector is empty (`m_size == 0`).
 */
void SVector::pop_back()
{
    if (m_size == 0) {
        throw std::out_of_range("Vector is empty");
    }

    --m_size;
}

// ============================================================================
// Element Accessors
// ============================================================================

/**
 * @brief Accesses an element at the specified index with bounds checking (read-only).
 *
 * @param[in] index Zero-based target index.
 * @return const int& Const reference to the integer at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
const int& SVector::at(int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
}

/**
 * @brief Accesses an element at the specified index with bounds checking (mutable).
 *
 * @param[in] index Zero-based target index.
 * @return int& Reference to the integer at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
int& SVector::at(int index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
}

/**
 * @brief Subscript access operator (mutable).
 *
 * @param[in] index Zero-based target element index.
 * @return int& Reference to the integer at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
int& SVector::operator[](int index) 
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

/**
 * @brief Subscript access operator (read-only).
 *
 * @param[in] index Zero-based target element index.
 * @return const int& Const reference to the integer at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= m_size`.
 */
const int& SVector::operator[](int index) const
{
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

// ============================================================================
// Assignment Operators
// ============================================================================

/**
 * @brief Deep copy assignment operator.
 *
 * @param[in] other Const reference to the source `SVector` to copy.
 * @return SVector& Reference to `*this`.
 *
 * @note Protects against self-assignment (`this == &other`). Frees existing memory 
 *       before allocating the new buffer.
 */
SVector& SVector::operator=(const SVector& other) 
{
    if (this == &other) return *this;

    delete[] m_data;

    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new int[m_capacity];

    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

/**
 * @brief Move assignment operator.
 *
 * @param[in,out] other Rvalue reference to the temporary `SVector` to move.
 * @return SVector& Reference to `*this`.
 *
 * @note Protects against self-assignment (`this != &other`). Deallocates existing 
 *       resources and nulls out source object metadata.
 */
SVector& SVector::operator=(SVector&& other) noexcept 
{
    if (this != &other) {
        delete[] m_data;

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

// ============================================================================
// Binary Operators & Utility
// ============================================================================

/**
 * @brief Binary addition operator. Concatenates two `SVector` instances into a new object.
 *
 * @param[in] other Right-hand side `SVector` operand to append.
 * @return SVector A new `SVector` containing elements of `*this` followed by elements of `other`.
 */
SVector SVector::operator+(const SVector& other) const {
    SVector result;
    result.m_size = m_size + other.m_size;
    result.m_capacity = result.m_size;
    result.m_data = new int[result.m_capacity];

    for (int i = 0; i < m_size; ++i) {
        result.m_data[i] = m_data[i];
    }
    for (int i = 0; i < other.m_size; ++i) {
        result.m_data[m_size + i] = other.m_data[i];
    }

    return result;
}

/**
 * @brief Utility output method. Prints formatted vector elements to standard output (`std::cout`).
 *
 * @note Outputs elements in array format (e.g., `[ 1 2 3 ]`).
 */
void SVector::display() const 
{
    std::cout << "[ ";
    for (int i = 0; i < m_size; ++i) 
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << "]\n";
}