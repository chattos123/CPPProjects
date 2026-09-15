/*
 * File: SDecendingPriorityQT.tpp
 * Implementation for SDecendingPriorityQT<T>.
 */

#include "SDecendingPriorityQT.h"

template <typename T>
bool SDecendingPriorityQT<T>::Enqueue(const T& val) 
{
    // If empty or val >= head, insert at head
    psNodeT<T> head = m_list.GetHead();
    // If the list is empty or the new value is greater than the head's value, insert at head
    if (!head || val > head->m_val) 
    {
        return m_list.AddHead(val);
    }

    // Traverse to find insertion point (descending order)
    psNodeT<T> prev = head;
    psNodeT<T> cur = head->m_next;
    int pos = 0;

    // Traverse until we find a node with a value less than the new value
    while (cur && cur->m_val >= val) 
    {
        prev = cur;
        cur = cur->m_next;
        ++pos;
    }
    // Insert after prev
    return m_list.AddElementAfter(pos, val);
}

template <typename T>
T SDecendingPriorityQT<T>::Dequeue() 
{
    psNodeT<T> head = m_list.GetHead();
    if (!head) throw std::out_of_range("SDecendingPriorityQT::Dequeue - empty queue");
    T val = head->m_val;
    if (!m_list.DeleteHead()) throw std::runtime_error("SDecendingPriorityQT::Dequeue - failed to delete head");
    return val;
}

template <typename T>
T SDecendingPriorityQT<T>::Front() const 
{
    psNodeT<T> head = m_list.GetHead();
    if (!head) throw std::out_of_range("SDecendingPriorityQT::Front - empty queue");
    return head->m_val;
}
