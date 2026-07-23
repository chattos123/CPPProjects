/***********************************************************************
* File: SListT.h
* Description: Declares the generic SListT template class for a type-safe singly-linked list in the DSA library.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

template <typename T>
struct tagNodeT {
    T m_val;
    tagNodeT* m_next;
};

template <typename T>
using sNodeT = tagNodeT<T>;

template <typename T>
using psNodeT = tagNodeT<T>*;

template <typename T>
/***********************************************************************
* Class: SListT<T>
*
* Purpose: Provides a templated singly-linked list implementation that
*          supports generic element insertion, removal, and traversal.
***********************************************************************/
class DSALIB_API SListT {
private:
    psNodeT<T> m_head;
    int m_count;

public:
    SListT();
    ~SListT();

    inline bool IsEmpty() const { return (m_head == nullptr); }
    inline int GetLength() const { return m_count; }

    bool AddElement(const T& val);
    psNodeT<T> GetElementAt(int index = 0);
    psNodeT<T> GetLastElement();
    bool DeleteElement();
    bool Display();
    bool AddElementAfter(int pos, const T& val);
    
    bool AddHead(const T& val);    // insert at head
    bool DeleteHead();             // remove head
    psNodeT<T> GetHead() const;    // return head node
};

//include implementation here
#include "SListT.tpp"
