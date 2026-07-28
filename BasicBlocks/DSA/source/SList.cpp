/**
 * @file SList.cpp
 * @brief Implementation of the SList singly-linked list class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SList.h"
#include <iostream>
#include <stdexcept>

/**
 * @brief Constructs an empty SList instance.
 *
 * Initializes the head pointer (`m_pListHead`) to nullptr and sets the element count (`m_iCount`) to 0.
 *
 * @param None
 */
SList::SList()
{
    m_pListHead = nullptr;
    m_iCount = 0;
}

/**
 * @brief Destructs the SList instance and frees dynamically allocated node memory.
 *
 * Iteratively traverses the linked list, deleting each node from head to tail to prevent memory leaks.
 * Resets the internal node counter upon completion.
 *
 * @param None
 */
SList::~SList()
{
    if (nullptr == m_pListHead)
    {
        return;
    }
    else
    {
        while (m_pListHead != nullptr)
        {
            psNode tempNode = m_pListHead->m_pNext;
            delete m_pListHead;
            m_pListHead = tempNode;
        }

        m_iCount = 0; // Reset node count
    }
}

/**
 * @brief Appends a new integer element to the end (tail) of the list.
 *
 * Allocates dynamic memory for a new node. If the list is empty, the node becomes the new head. 
 * Otherwise, the list is traversed to the tail node to append the new node.
 *
 * @param[in] iVal Integer value to store in the newly appended node.
 * @return true If the node was successfully created and appended.
 * @return false If memory allocation for the new node failed.
 * @remark Increments `m_iCount` upon successful insertion.
 */
bool SList::AddElement(int iVal)
{
    bool bRetval = false;
    psNode pTempNode = nullptr;
    psNode psCountNode = nullptr;

    if (m_pListHead == nullptr)
    {
        m_pListHead = new sNode();
        if (m_pListHead)
        {
            bRetval = true;
            m_pListHead->m_iVal = iVal;
            m_pListHead->m_pNext = nullptr;
            m_iCount++;
            return bRetval;
        }
        else
        {
            return bRetval;
        }
    }
    else
    {
        psCountNode = m_pListHead;

        while (psCountNode->m_pNext != nullptr)
        {
            psCountNode = psCountNode->m_pNext;
        }

        pTempNode = new sNode();

        if (pTempNode)
        {
            bRetval = true;
            pTempNode->m_iVal = iVal;
            pTempNode->m_pNext = nullptr;
            psCountNode->m_pNext = pTempNode;
            m_iCount++;
            return bRetval;
        }
        else
        {
            return bRetval;
        }
    }
}

/**
 * @brief Retrieves a pointer to the node located at the specified zero-based index.
 *
 * Sequentially traverses the linked list from the head node up to the target index position.
 *
 * @param[in] iCount Zero-based index position of the requested node (defaults to 0 for head node).
 * @return psNode Pointer to the target node if index is valid; nullptr if index is out of bounds or list is uninitialized.
 */
psNode SList::GetElementAt(int iCount)
{
    int iCnt = 0;

    if (iCount == 0)
    {
        if (m_pListHead)
        {
            return m_pListHead;
        }
        else
        {
            std::cout << "ERROR::Create List First";
            return nullptr;
        }
    }

    if (iCount > m_iCount)
    {
        return nullptr;
    }
    else
    {
        if (nullptr == m_pListHead)
        {
            std::cout << "ERROR::Create List First";
            return nullptr;
        }
        else
        {
            psNode pTempNode = m_pListHead;
            while (iCnt < iCount)
            {
                pTempNode = pTempNode->m_pNext;
                iCnt++;
            }
            if (pTempNode)
            {
                return pTempNode;
            }
            else
            {
                return nullptr;
            }
        }
    }
}

/**
 * @brief Retrieves a pointer to the last (tail) node in the linked list.
 *
 * Traverses from the head node along next-pointers until reaching the terminal node.
 *
 * @param None
 * @return psNode Pointer to the tail node; nullptr if the list is empty or uninitialized.
 */
psNode SList::GetLastElement()
{
    if (nullptr == m_pListHead)
    {
        std::cout << "ERROR::Create List First";
        return nullptr;
    }
    else
    {
        psNode pTempNode = m_pListHead;
        while (pTempNode->m_pNext != nullptr)
        {
            pTempNode = pTempNode->m_pNext;
        }
        if (pTempNode)
        {
            return pTempNode;
        }
        else
        {
            return nullptr;
        }
    }
}

/**
 * @brief Removes and deallocates the last (tail) node from the linked list.
 *
 * Traverses the list to locate the tail node and its preceding node. Updates the preceding node's 
 * next-pointer to nullptr and deletes the tail node.
 *
 * @param None
 * @return true If the tail element was successfully deleted.
 * @return false If the list was empty or deletion failed.
 * @remark Decrements `m_iCount` on successful removal.
 */
bool SList::DeleteElement()
{
    bool bRetval = false;
    if (nullptr == m_pListHead)
    {
        std::cout << "ERROR::List is Empty, Cannot Delete";
        return bRetval;
    }
    else
    {
        psNode pTempNode = m_pListHead;
        psNode pIndexNode = pTempNode->m_pNext;

        if (nullptr == pIndexNode)
        {
            bRetval = true;
            delete pTempNode;
            pTempNode = nullptr;
            m_pListHead = nullptr;
            m_iCount--;
            return bRetval;
        }
        else
        {
            while (pIndexNode->m_pNext != nullptr)
            {
                pIndexNode = pIndexNode->m_pNext;
                pTempNode = pTempNode->m_pNext;
            }

            if (pIndexNode)
            {
                bRetval = true;
                pTempNode->m_pNext = nullptr;
                delete pIndexNode;
                pIndexNode = nullptr;
                m_iCount--;
                return bRetval;
            }
            else
            {
                return bRetval;
            }
        }
    }
}

/**
 * @brief Prints the formatted contents of the linked list sequentially to standard output.
 *
 * Iterates through all nodes starting from `m_pListHead` and prints element indices and values 
 * formatted as `E0=val1  E1=val2 ...`.
 *
 * @param None
 * @return true If traversal and output completed successfully.
 * @return false If the list was empty.
 * @remark Non-destructive traversal method.
 */
bool SList::Display()
{
    int iCnt = 0;
    psNode pCountNode = m_pListHead;

    if (nullptr == pCountNode)
    {
        std::cout << "Now the List is empty\n\n";
        return false;
    }
    else
    {
        do
        {
            std::cout << "E" << iCnt << "=" << pCountNode->m_iVal << "\t";
            pCountNode = pCountNode->m_pNext;
            iCnt++;

        } while (pCountNode != nullptr);

        std::cout << "\n\n";
        return true;
    }
}

/**
 * @brief Inserts a new integer node immediately after the specified zero-based index position.
 *
 * Allocates a new node, locates the node at `iNodepos`, and adjusts pointer links to insert 
 * the new node into the list.
 *
 * @param[in] iNodepos Zero-based index position after which the new element should be placed.
 * @param[in] iVal Integer value to store in the new node.
 * @return true If the node was successfully created and inserted.
 * @return false If target index was out of bounds or list was uninitialized.
 * @remark Increments `m_iCount` upon successful insertion.
 */
bool SList::AddElementAfter(int iNodepos, const int iVal)
{
    bool bRetval = false;
    if (m_pListHead)
    {
        if (iNodepos > (m_iCount - 1))
        {
            std::cout << "ERROR: Cannot Insert an element here";
            return false;
        }
        else
        {
            psNode pNewnode = new sNode();
            if (pNewnode)
            {
                psNode pTempNode = GetElementAt(iNodepos);

                if (pTempNode)
                {
                    bRetval = true;
                    pNewnode->m_pNext = pTempNode->m_pNext;
                    pTempNode->m_pNext = pNewnode;
                    pNewnode->m_iVal = iVal;
                    m_iCount++;
                    return bRetval;
                }
                else
                {
                    return bRetval;
                }
            }
            else
            {
                return bRetval;
            }
        }
    }
    else
    {
        std::cout << "ERROR: List is not created yet!";
        return bRetval;
    }
}