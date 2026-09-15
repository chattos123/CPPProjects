/**
 * @file SStrictBTree.h
 * @brief Declares the SStrictBTree template class for a strictly binary tree.
 *        Includes Big-O complexity annotations for key operations.
 * @author Soumyajit
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @struct tagBNodeT
 * @brief Represents a node in the strictly binary tree.
 *
 * @tparam T Type of value stored within the node.
 */
template <typename T>
struct tagBNodeT
{
    T m_val;            ///< Stored element value.
    tagBNodeT *m_left;  ///< Pointer to left child.
    tagBNodeT *m_right; ///< Pointer to right child.

    tagBNodeT(const T &val)
        : m_val(val), m_left(nullptr), m_right(nullptr) {}
};

/// Type alias for tagBNodeT<T>
template <typename T>
using sBNodeT = tagBNodeT<T>;

/// Type alias for pointer to tagBNodeT<T>
template <typename T>
using psBNodeT = tagBNodeT<T> *;

/**
 * @class SStrictBTree
 * @brief Strict binary tree container supporting insertion, deletion, and traversal.
 *
 * @tparam T Type of elements stored in the tree.
 */
template <typename T>
class SStrictBTree
{
private:
    psBNodeT<T> m_root; ///< Root node of the tree.
    int m_count;        ///< Total number of nodes.

    // Helper: recursive deep copy
    psBNodeT<T> CopyFrom(psBNodeT<T> other)
    {
        if (!other)
            return nullptr;
        psBNodeT<T> node = new sBNodeT<T>(other->m_val);
        node->m_left = CopyFrom(other->m_left);
        node->m_right = CopyFrom(other->m_right);
        return node;
    }

    // Helper: recursive clear
    void Clear(psBNodeT<T> node)
    {
        if (!node)
            return;
        Clear(node->m_left);
        Clear(node->m_right);
        delete node;
    }

public:
    /// Constructor — O(1)
    SStrictBTree() : m_root(nullptr), m_count(0) {}

    /// Destructor — O(n), frees all nodes
    ~SStrictBTree() { Clear(m_root); }

    /// Copy constructor — O(n), deep copy of all nodes
    SStrictBTree(const SStrictBTree &other)
    {
        m_root = CopyFrom(other.m_root);
        m_count = other.m_count;
    }

    /// Copy assignment — O(n), deep copy
    SStrictBTree &operator=(const SStrictBTree &other)
    {
        if (this != &other)
        {
            Clear(m_root);
            m_root = CopyFrom(other.m_root);
            m_count = other.m_count;
        }
        return *this;
    }

    /// Move constructor — O(1)
    SStrictBTree(SStrictBTree &&other) noexcept
        : m_root(other.m_root), m_count(other.m_count)
    {
        other.m_root = nullptr;
        other.m_count = 0;
    }

    /// Move assignment — O(1)
    SStrictBTree &operator=(SStrictBTree &&other) noexcept
    {
        if (this != &other)
        {
            Clear(m_root);
            m_root = other.m_root;
            m_count = other.m_count;
            other.m_root = nullptr;
            other.m_count = 0;
        }

        return *this;
    }

    /// Check if tree is empty — O(1)
    inline bool IsEmpty() const { return (m_root == nullptr); }

    /// Get number of nodes — O(1)
    inline int GetCount() const { return m_count; }

    /**
     * @brief Insert a new node with two children (strict binary rule).
     * @param val Value to insert.
     * @return true if inserted successfully, false otherwise.
     * @remark Complexity: O(n) in worst case (level-order traversal).
     */
    bool InsertStrict(const T &val);

    /**
     * @brief Display tree in-order.
     * @return true if traversal succeeded, false if empty.
     * @remark Complexity: O(n), visits all nodes.
     */
    bool DisplayInOrder();

    /**
     * @brief Get root node.
     * @return Pointer to root node.
     * @remark Complexity: O(1)
     */
    psBNodeT<T> GetRoot() const { return m_root; }

    /**
     * @brief Retrieves the left child of a given node.
     * @param[in] p Pointer to the node whose left child is requested.
     * @return psBNodeT<T> Pointer to the left child, or nullptr if none.
     */
    template <typename T>
    psBNodeT<T> SStrictBTree<T>::left(psBNodeT<T> p)
    {
        if (!p)
            return nullptr;
        return p->m_left;
    }

    /**
     * @brief Retrieves the right child of a given node.
     * @param[in] p Pointer to the node whose right child is requested.
     * @return psBNodeT<T> Pointer to the right child, or nullptr if none.
     */
    template <typename T>
    psBNodeT<T> SStrictBTree<T>::right(psBNodeT<T> p)
    {
        if (!p)
            return nullptr;
        return p->m_right;
    }
};

// Include template implementation definitions
#include "SStrictBTree.tpp"