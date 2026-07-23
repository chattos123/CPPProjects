/***********************************************************************
* File: SVector.cpp
* Description: Implements the SVector dynamic array class for the DSA library.
***********************************************************************/
#include <stdexcept>
#include <iostream>
#include "SVector.h"

#define VECTOR_ATOMICITY 2

/***********************************************************************/
/// <b>Function: SVector</b>
///
/// <b>remarks</b>    Default constructor initializes an empty vector.
///
/***********************************************************************/
SVector::SVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

/***********************************************************************/
/// <b>Function: SVector</b>
///
/// <b>brief</b>      Copy constructor performs deep copy of vector contents.
///
/***********************************************************************/
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

/***********************************************************************/
/// <b>Function: ~SVector</b>
///
/// <b>remarks</b>    Releases allocated vector storage.
///
/***********************************************************************/
SVector::~SVector() 
{
    delete[] m_data;
    m_data = nullptr; // avoid dangling pointer
}

/***********************************************************************/
/// <b>Function: resize</b>
///
/// <b>brief</b>      Resizes the internal storage array.
///
/***********************************************************************/
void SVector::resize(int newCapacity) {
    int* newData = new int[newCapacity];
    for (int i = 0; i < m_size; ++i) {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

/***********************************************************************/
/// <b>Function: push_back</b>
///
/// <b>brief</b>      Appends a new value to the end of the vector.
///
/***********************************************************************/
void SVector::push_back(int value) 
{
    if (m_size == m_capacity) 
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * VECTOR_ATOMICITY;
        resize(newCapacity);
    }

    m_data[m_size++] = value;
}

/***********************************************************************/
/// <b>Function: pop_back</b>
///
/// <b>brief</b>      Removes the last element from the vector.
///
/***********************************************************************/
void SVector::pop_back()
 {
    if (m_size == 0) {
        throw std::out_of_range("Vector is empty");
    }

    --m_size;
}

/***********************************************************************/
/// <b>Function: at</b>
///
/// <b>brief</b>      Returns the value at the specified index with bounds checking.
///
/***********************************************************************/
int SVector::at(int index) const 
{
    if (index < 0 || index >= m_size) 
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

/***********************************************************************/
/// <b>Function: display</b>
///
/// <b>brief</b>      Prints the contents of the vector to standard output.
///
/***********************************************************************/
void SVector::display() const 
{
    std::cout << "[ ";
    for (int i = 0; i < m_size; ++i) 
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << "]\n";
}

/***********************************************************************/
/// <b>Function: operator[]</b>
///
/// <b>brief</b>      Returns a reference to the element at the given index.
///
/***********************************************************************/
int& SVector::operator[](int index) 
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

/***********************************************************************/
/// <b>Function: operator[]</b>
///
/// <b>brief</b>      Returns a const reference to the element at the given index.
///
/***********************************************************************/
const int& SVector::operator[](int index) const
{
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[index];
}

/***********************************************************************/
/// <b>Function: operator=</b>
///
/// <b>brief</b>      Performs deep copy assignment from another vector.
///
/***********************************************************************/
SVector& SVector::operator=(const SVector& other) 
{
    if (this == &other) return *this; // self-assignment check

    delete[] m_data; // free old memory
    m_data = nullptr; // avoid dangling pointer

    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new int[m_capacity];

    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

/***********************************************************************/
/// <b>Function: operator+</b>
///
/// <b>brief</b>      Concatenates two vectors into a new result vector.
///
/***********************************************************************/
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

