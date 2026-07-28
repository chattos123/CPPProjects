/**
 * @file SListT.h
 * @brief Declares the generic SListT template class for a type-safe singly-linked list.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @struct tagNodeT
 * @brief Represents an individual node in the templated singly-linked list.
 *
 * @tparam T Type of value stored within the node.
 */
template <typename T>
struct tagNodeT {
    T m_val;            ///< Stored element value.
    tagNodeT* m_next;   ///< Pointer to the next node in the list.
};

/// Type alias for tagNodeT<T> structure.
template <typename T>
using sNodeT = tagNodeT<T>;

/// Type alias for pointer to a tagNodeT<T> structure.
template <typename T>
using psNodeT = tagNodeT<T>*;

/**
 * @class SListT
 * @brief Generic singly-linked list container supporting type-safe node insertion, deletion, and traversal.
 *
 * @tparam T Type of elements stored within the singly-linked list.
 */
template <typename T>
class SListT 
{
private:
    psNodeT<T> m_head;  ///< Pointer to the head node of the list.
    int m_count;        ///< Total number of active nodes in the list.

    //Fix: Memory Leak in Rehash in SHashMap.pp
    // SListT owns a linked list which defines a destructor but not copy constructor
    // or assignmen operator. The compiler generated version do a shallow copy
    // so any by value copy od SList creates 2 objects taht own a same not
    // that's why shashmap rehash crashes.
    /* for (int i = 0; i < m_capacity; ++i) {
        auto bucket = m_buckets[i];
        auto node = bucket.GetHead();
        while (node) {
            int newIndex = m_hasher(node->m_val.first) % newCapacity;
            newBuckets[newIndex].AddElement(node->m_val);
            node = node->m_next;
        }
    }*/
    //  SVectorT<SListT<SPair<K, V>>> m_buckets; ///< Dynamic array of singly-linked lists serving as hash buckets.
    // so in each loop iteration bucket shares node pointer with m_buckets[i]
    // when bucket goes out of scope its descructor frees every node-but mbuckets[i]
    // still points to that freed null memory...
    //subsquent delete[] inside SVectorT causes double free heap corruption
    // so fixed here by adding copy constructor  and assignement and move costructor and assignment
    
    // Helper to deep copy nodes
    void CopyFrom(const SListT& other) {
        m_head = nullptr;
        m_count = 0;
        psNodeT<T> current = other.m_head;
        while (current) {
            AddElement(current->m_val);
            current = current->m_next;
        }
    }

    // Helper to free nodes
    void Clear() {
        while (m_head) {
            psNodeT<T> temp = m_head->m_next;
            delete m_head;
            m_head = temp;
        }
        m_count = 0;
    }

public:
    /**
     * @brief Constructs an empty SListT instance.
     *
     * Initializes the head pointer to nullptr and node count to 0.
     *
     * @param None  
     * @return None
     */
    SListT();

    /**
     * @brief Destructs the SListT instance and frees all allocated node memory.
     *
     * Iteratively deallocates all nodes to prevent memory leaks.
     *
     * @param None
     * @return None
     */
    ~SListT();

    // Copy constructor (deep copy)
    SListT(const SListT& other) 
    {
        CopyFrom(other);
    }

    // Copy assignment (deep copy)
    SListT& operator=(const SListT& other) 
    {
        if (this != &other) 
        {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }

    // Move constructor
    SListT(SListT&& other) noexcept
        : m_head(other.m_head), m_count(other.m_count) 
    {
        other.m_head = nullptr;
        other.m_count = 0;
    }

    // Move assignment
    SListT& operator=(SListT&& other) noexcept 
    {
        if (this != &other) {
            Clear();
            m_head = other.m_head;
            m_count = other.m_count;
            other.m_head = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    /**
     * @brief Checks whether the list contains any nodes.
     *
     * @param None
     * @return true If the list head pointer is nullptr.
     * @return false If the list contains one or more nodes.
     * @remark Inline query providing O(1) time complexity.
     */
    inline bool IsEmpty() const { return (m_head == nullptr); }

    /**
     * @brief Retrieves the current count of elements stored in the list.
     *
     * @param None
     * @return int The current number of nodes.
     * @remark Inline query providing O(1) time complexity.
     */
    inline int GetLength() const { return m_count; }

    /**
     * @brief Appends a new value to the end (tail) of the list.
     *
     * @param[in] val Constant reference to the element value to append.
     * @return true If the element was successfully created and appended.
     * @return false If memory allocation for the node failed.
     * @remark Increments node count on success.
     */
    bool AddElement(const T& val);

    /**
     * @brief Retrieves a pointer to the node at the specified 0-based index.
     *
     * @param[in] index 0-based index position of target node (defaults to 0 for head).
     * @return psNodeT<T> Pointer to target node, or nullptr if index is out of bounds.
     * @remark Traverses list sequentially starting from head pointer.
     */
    psNodeT<T> GetElementAt(int index = 0);

    /**
     * @brief Retrieves a pointer to the last (tail) node in the list.
     *
     * @param None
     * @return psNodeT<T> Pointer to the tail node, or nullptr if list is empty.
     */
    psNodeT<T> GetLastElement();

    /**
     * @brief Deletes the last (tail) node in the list.
     *
     * @param None
     * @return true If a node was successfully removed.
     * @return false If the list was empty.
     * @remark Decrements internal node count on successful deletion.
     */
    bool DeleteElement();

    /**
     * @brief Outputs all element values sequentially to standard output.
     *
     * @param None
     * @return true If traversal and display completed successfully.
     * @return false If the list is empty.
     * @remark Non-destructive traversal requiring operator<< to be defined for type T.
     */
    bool Display();

    /**
     * @brief Inserts a new value immediately following the node at the specified position index.
     *
     * @param[in] pos 0-based index position after which the new node will be inserted.
     * @param[in] val Constant reference to the element value to insert.
     * @return true If insertion succeeded.
     * @return false If target index position was out of bounds or node creation failed.
     */
    bool AddElementAfter(int pos, const T& val);

    /**
     * @brief Inserts a new element at the front (head) of the list.
     *
     * @param[in] val Constant reference to the element value to insert at head.
     * @return true If head node insertion succeeded.
     * @return false If memory allocation failed.
     * @remark Provides O(1) insertion time at the front of the list.
     */
    bool AddHead(const T& val);

    /**
     * @brief Removes the element at the front (head) of the list.
     *
     * @param None
     * @return true If the head node was successfully deleted.
     * @return false If the list was empty.
     * @remark Provides O(1) removal time from the front of the list.
     */
    bool DeleteHead();

    /**
     * @brief Retrieves a const pointer to the current head node.
     *
     * @param None
     * @return psNodeT<T> Pointer to head node, or nullptr if list is empty.
     * @remark Non-destructive getter method.
     */
    psNodeT<T> GetHead() const;
};

// Include template implementation definitions
#include "SListT.tpp"