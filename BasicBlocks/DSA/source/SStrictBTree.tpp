/**
 * @file SStrictBTree.tpp
 * @brief Implements the SStrictBTree template class methods.
 */

#pragma once
#include <iostream>

// InsertStrict: ensures strict binary property (0 or 2 children)
template <typename T>
bool SStrictBTree<T>::InsertStrict(const T& val) 
{
    psBNodeT<T> newNode = new sBNodeT<T>(val);
    if (!newNode) return false;

    if (!m_root) 
    {
        m_root = newNode;
        ++m_count;
        return true;
    }

    // Level-order traversal to find a node with 0 children
    std::queue<psBNodeT<T>> q;
    q.push(m_root);

    while (!q.empty()) 
    {
        psBNodeT<T> current = q.front();
        q.pop();

        // Case: node has no children → attach both left & right
        if (!current->m_left && !current->m_right) 
        {
            current->m_left = newNode;
            current->m_right = new sBNodeT<T>(val); // duplicate for strictness
            m_count += 2;
            return true;
        }

        // Case: node has exactly one child → violation
        if ((current->m_left && !current->m_right) ||
            (!current->m_left && current->m_right)) 
        {
            std::cerr << "Strict binary rule violated: node has only one child.\n";
            delete newNode;
            return false;
        }

        // Continue traversal
        if (current->m_left) q.push(current->m_left);
        if (current->m_right) q.push(current->m_right);
    }

    return false;
}

// In-order traversal
template <typename T>
bool SStrictBTree<T>::DisplayInOrder() 
{
    if (!m_root) 
    {
        std::cout << "Tree is empty\n";
        return false;
    }

    std::function<void(psBNodeT<T>)> inorder = [&](psBNodeT<T> node) 
    {
        if (!node) return;
        inorder(node->m_left);
        std::cout << node->m_val << " ";
        inorder(node->m_right);
    };

    inorder(m_root);
    std::cout << "\n";
    return true;
}