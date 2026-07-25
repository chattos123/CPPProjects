/***********************************************************************
* File: SList.h
* Description: Declares the SList class for a singly-linked list in the DSA library.
***********************************************************************/
#pragma once

#include "ExportMacro.h"

struct tagNode {
    int m_iVal;
    tagNode* m_pNext;
};

using sNode = tagNode;
using psNode = tagNode*;

/***********************************************************************
* Class: SList
*
* Purpose: Implements a simple singly-linked list with insertion,
*          deletion, traversal, and display operations.
***********************************************************************/
class DSA_API SList
{
private:
    psNode m_pListHead;
    int m_iCount;

public:
    SList();
    ~SList();

    /** @brief Checks whether the list is empty. */
    inline bool IsEmpty() const {
        return (m_pListHead == nullptr);
    }
    
    /** @brief Returns the number of elements in the list. */
    inline int GetLength() const {
        return m_iCount;
    }

    // Member functions
    bool AddElement(int iVal);
    psNode GetElementAt(int iCount = 0);
    psNode GetLastElement();
    bool DeleteElement();
    bool Display();
    bool AddElementAfter(int iNodepos, int iVal);
};