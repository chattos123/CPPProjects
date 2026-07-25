/***********************************************************************
* File: SVector.h
* Description: Declares the SVector class for a dynamic array container in the DSA library.
***********************************************************************/
#pragma once

#include "ExportMacro.h"

/***********************************************************************
* Class: SVector
*
* Purpose: Implements a simple resizable array container with push/pop,
*          indexing, and element-wise concatenation support.
***********************************************************************/
class DSA_API SVector {
private:
    int* m_data;       // Pointer to dynamic memory
    int m_size;        // Number of active elements
    int m_capacity;    // Total allocated slots

    void resize(int newCapacity);

public:
    // ---------------- Constructors & Destructor ----------------
    SVector();                                 // Default constructor
    ~SVector();                                // Destructor
    
    SVector(const SVector& other);             // Copy constructor
    SVector& operator=(const SVector& other);  // Copy assignment

    SVector(SVector&& other) noexcept;         // Move constructor
    SVector& operator=(SVector&& other) noexcept; // Move assignment

    // ---------------- Element Access & Modifiers ----------------
    void push_back(int value);
    void pop_back();
    
    int& at(int index);
    const int& at(int index) const;

    inline int size() const { return m_size; }
    inline int capacity() const { return m_capacity; }
    inline bool empty() const { return m_size == 0; }

    void display() const;

    // ---------------- Operator Overloads ----------------
    int& operator[](int index);
    const int& operator[](int index) const;

    SVector operator+(const SVector& other) const;
};