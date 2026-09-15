/*
 * File: SAssendingPriorityQT.tpp
 * Implementation for SAssendingPriorityQT<T>.
 */

#include "SAssendingPriorityQT.h"

template <typename T>
bool SAssendingPriorityQT<T>::Enqueue(const T& val) 
{
    // If empty or val <= head, insert at head
    psNodeT<T> head = m_list.GetHead();

    if (!head || val < head->m_val) 
    {
        return m_list.AddHead(val);
    }

    // Traverse to find insertion point
    psNodeT<T> prev = head;
    psNodeT<T> cur = head->m_next;
    int pos = 0;
    
    while (cur && cur->m_val <= val) 
    {
        prev = cur;
        cur = cur->m_next;
        ++pos;
    }
    // Insert after prev
    return m_list.AddElementAfter(pos, val);
}

template <typename T>
T SAssendingPriorityQT<T>::Dequeue() 
{
    psNodeT<T> head = m_list.GetHead();
    if (!head) throw std::out_of_range("SAssendingPriorityQT::Dequeue - empty queue");
    T val = head->m_val;
    if (!m_list.DeleteHead()) throw std::runtime_error("SAssendingPriorityQT::Dequeue - failed to delete head");
    return val;
}

template <typename T>
T SAssendingPriorityQT<T>::Front() const 
{
    psNodeT<T> head = m_list.GetHead();
    if (!head) throw std::out_of_range("SAssendingPriorityQT::Front - empty queue");
    return head->m_val;
}
