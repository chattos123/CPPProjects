/**
 * @file SList.h
 * @brief Declares the SList class and node structures for a singly-linked list in the DSA library.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @struct tagNode
 * @brief Represents an individual node structure within the singly-linked list.
 */
struct tagNode 
{
    int m_iVal;         ///< Integer value stored in the node.
    tagNode* m_pNext;   ///< Pointer to the next node in the linked list.
};

/// Type alias for tagNode structure.
using sNode = tagNode;

/// Type alias for pointer to a tagNode structure.
using psNode = tagNode*;

/**
 * @class SList
 * @brief Implements a singly-linked list supporting insertion, deletion, positioning, and display operations.
 * 
 * Exported via DSA_API for dynamic library usage. Manages dynamically allocated node memory.
 */
class DSA_API SList
{
private:
    psNode m_pListHead; ///< Pointer to the head node of the singly-linked list.
    int m_iCount;       ///< Stores the current number of nodes present in the list.

public:
    /**
     * @brief Constructs an empty SList instance.
     * 
     * Initializes head pointer to nullptr and node count to 0.
     *
     * @param None
     * @return None
     */
    SList();

    /**
     * @brief Destructs the SList instance and frees allocated node memory.
     * 
     * Iteratively deallocates all remaining nodes to prevent memory leaks.
     *
     * @param None
     * @return None
     */
    ~SList();

    /**
     * @brief Checks whether the list contains any nodes.
     *
     * @param None
     * @return true If the list head is nullptr.
     * @return false If the list contains one or more nodes.
     * @remark Inline function for fast execution.
     */
    inline bool IsEmpty() const {
        return (m_pListHead == nullptr);
    }
    
    /**
     * @brief Retrieves the current total count of elements stored in the list.
     *
     * @param None
     * @return int The total number of active nodes.
     * @remark Inline getter providing O(1) complexity access to member count.
     */
    inline int GetLength() const {
        return m_iCount;
    }

    /**
     * @brief Inserts a new integer element at the end of the linked list.
     *
     * @param[in] iVal Integer value to append to the list.
     * @return true If the node allocation and insertion succeeded.
     * @return false If memory allocation for the new node failed.
     * @remark Increments internal node counter upon successful insertion.
     */
    bool AddElement(int iVal);

    /**
     * @brief Retrieves a node pointer located at the specified 0-based index position.
     *
     * @param[in] iCount 0-based index position of target node (defaults to 0 for head node).
     * @return psNode Pointer to target node if index is valid; nullptr if index is out of bounds.
     * @remark Traverses list sequentially starting from head pointer.
     */
    psNode GetElementAt(int iCount = 0);

    /**
     * @brief Retrieves a pointer to the last tail node in the list.
     *
     * @param None
     * @return psNode Pointer to the last node; nullptr if list is empty.
     */
    psNode GetLastElement();

    /**
     * @brief Removes the last element from the end of the list.
     *
     * @param None
     * @return true If an element was successfully deleted.
     * @return false If the list was empty and no node could be removed.
     * @remark Decrements node count and handles updating previous node pointer references.
     */
    bool DeleteElement();

    /**
     * @brief Outputs all current list elements sequentially to stdout.
     *
     * @param None
     * @return true If traversal and display completed successfully.
     * @return false If the list is empty.
     * @remark Non-destructive traversal function.
     */
    bool Display();

    /**
     * @brief Inserts a new integer element immediately following the node at the target index.
     *
     * @param[in] iNodepos 0-based position index after which the new element should be placed.
     * @param[in] iVal Integer value to insert.
     * @return true If the node was successfully inserted.
     * @return false If target index position was out of bounds or node creation failed.
     */
    bool AddElementAfter(int iNodepos, int iVal);
};