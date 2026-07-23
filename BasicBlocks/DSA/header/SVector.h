/***********************************************************************
* File: SVector.h
* Description: Declares the SVector class for a dynamic array container in the DSA library.
***********************************************************************/
#pragma once
#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

/***********************************************************************
* Class: SVector
*
* Purpose: Implements a simple resizable array container with push/pop,
*          indexing, and element-wise concatenation support.
***********************************************************************/
class DSALIB_API SVector {
private:
    int* m_data;       // pointer to dynamic array
    int m_size;        // number of elements
    int m_capacity;    // allocated capacity

    void resize(int newCapacity);

public:
    SVector();// default constructor
    ~SVector();// destructor
    SVector(const SVector& other);// copy constructor

    void push_back(int value);
    void pop_back();
    int at(int index) const;
    int size() const { return m_size; }
    int capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }

    void display() const;

    //operator overloads
    int& operator[](int index);        // non-const version (allows modification)
    const int& operator[](int index) const; // const version (read-only)
    SVector& operator=(const SVector& other); // assignment operator overload
    SVector operator+(const SVector& other) const;// readonly Addition operator overload
};
