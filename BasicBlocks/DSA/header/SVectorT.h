/***********************************************************************
* File: SVectorT.h
* Description: Declares the templated SVectorT class for a type-safe dynamic array container.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <stdexcept>


template <typename T>
/***********************************************************************
* Class: SVectorT<T>
*
* Purpose: A generic resizable vector container supporting deep copy,
*          move semantics, iteration, and basic element operations.
***********************************************************************/
class DSALIB_API SVectorT {
private:
    T* m_data;
    int m_size;
    int m_capacity;

    void resize(int newCapacity);

public:

    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() { return m_data; }
    iterator end() { return m_data + m_size; }
    const_iterator begin() const { return m_data; }
    const_iterator end() const { return m_data + m_size; }
    const_iterator cbegin() const { return m_data; }
    const_iterator cend() const { return m_data + m_size; }

    /***********************************************************************/
    /// <b>Function: SVectorT</b>
    ///
    /// \remarks    Default constructor creates an empty vector.
    ///
    /***********************************************************************/
    SVectorT();                          // default constructor

    /***********************************************************************/
    /// <b>Function: ~SVectorT</b>
    ///
    /// \remarks    Destructor releases all allocated storage.
    ///
    /***********************************************************************/
    ~SVectorT();                         // destructor

    /***********************************************************************/
    /// <b>Function: SVectorT</b>
    ///
    /// \brief      Copy constructor performs a deep copy of another vector.
    ///
    /***********************************************************************/
    SVectorT(const SVectorT& other);     // copy constructor

    /***********************************************************************/
    /// <b>Function: SVectorT</b>
    ///
    /// \brief      Move constructor transfers ownership from another vector.
    ///
    /***********************************************************************/
    SVectorT(SVectorT&& other) noexcept;             // move constructor

    /***********************************************************************/
    /// <b>Function: operator=</b>
    ///
    /// \brief      Copy assignment operator performs a deep copy.
    ///
    /***********************************************************************/
    SVectorT& operator=(const SVectorT& other); // assignment operator

    /***********************************************************************/
    /// <b>Function: operator+</b>
    ///
    /// \brief      Concatenates two vectors into a new vector.
    ///
    /***********************************************************************/
    SVectorT operator+(const SVectorT& other) const; // addition operator

    /***********************************************************************/
    /// <b>Function: operator=</b>
    ///
    /// \brief      Move assignment operator transfers ownership.
    ///
    /***********************************************************************/
    SVectorT& operator=(SVectorT&& other) noexcept;  // move assignment


    /***********************************************************************/
    /// <b>Function: push_back</b>
    ///
    /// \brief      Adds a value to the end of the vector.
    ///
    /***********************************************************************/
    void push_back(const T& value);

    /***********************************************************************/
    /// <b>Function: pop_back</b>
    ///
    /// \brief      Removes the last element from the vector.
    ///
    /***********************************************************************/
    void pop_back();

    /***********************************************************************/
    /// <b>Function: at</b>
    ///
    /// \brief      Returns the element at the specified index with bounds checking.
    ///
    /***********************************************************************/
    T at(int index) const;

    /***********************************************************************/
    /// <b>Function: operator[]</b>
    ///
    /// \brief      Returns a mutable reference to the element at the specified index.
    ///
    /***********************************************************************/
    T& operator[](int index);

    /***********************************************************************/
    /// <b>Function: operator[]</b>
    ///
    /// \brief      Returns a const reference to the element at the specified index.
    ///
    /***********************************************************************/
    const T& operator[](int index) const;

    int size() const { return m_size; }
    int capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }

    /***********************************************************************/
    /// <b>Function: reserve</b>
    ///
    /// \brief      Reserves capacity for at least newCapacity elements.
    ///
    /***********************************************************************/
    void reserve(int newCapacity);

    /***********************************************************************/
    /// <b>Function: resizeSize</b>
    ///
    /// \brief      Changes the logical element count of the vector.
    ///
    /***********************************************************************/
    void resizeSize(int newSize);

    /***********************************************************************/
    /// <b>Function: display</b>
    ///
    /// \brief      Prints vector contents to standard output.
    ///
    /***********************************************************************/
    void display() const;
};

// include template implementation
#include "SVectorT.tpp"
