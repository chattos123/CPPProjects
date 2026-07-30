/*
 * File: SListCircularQT.tpp
 * Implementation for SListCircularQT<T> using SListT<T>.
 */

#include "SListCircularQT.h"

// PushBack (copy)
template <typename T>
bool SListCircularQT<T>::PushBack(const T& val) 
{
    return m_list.AddElement(val);
}

// PushBack (move)
template <typename T>
bool SListCircularQT<T>::PushBack(T&& val) 
{
    return m_list.AddElement(std::move(val));
}

// PushFront (copy)
template <typename T>
bool SListCircularQT<T>::PushFront(const T& val) 
{
    return m_list.AddHead(val);
}

// PushFront (move)
template <typename T>
bool SListCircularQT<T>::PushFront(T&& val) 
{
    return m_list.AddHead(std::move(val));
}

// PopFront
template <typename T>
T SListCircularQT<T>::PopFront() 
{
    psNodeT<T> head = m_list.GetHead();
    if (!head) throw std::out_of_range("SListCircularQT::PopFront - list is empty");
    T val = std::move(head->m_val);
    if (!m_list.DeleteHead()) throw std::runtime_error("SListCircularQT::PopFront - DeleteHead failed");
    return val;
}

// Rotate
template <typename T>
void SListCircularQT<T>::Rotate() 
{
    int n = Size();
    if (n <= 1) return;
    // Move head to tail: pop front then push back
    T v = PopFront();
    // If push back fails (allocation), we reinsert at front to preserve state
    if (!PushBack(std::move(v))) {
        // attempt to restore original by pushing front (best-effort)
        PushFront(std::move(v));
        throw std::runtime_error("SListCircularQT::Rotate - allocation failed while rotating");
    }
}

// Contains
template <typename T>
bool SListCircularQT<T>::Contains(const T& val) const 
{
    psNodeT<T> cur = m_list.GetHead();

    while (cur) 
    {
        if (cur->m_val == val) return true;
        cur = cur->m_next;
    }
    return false;
}

// ---------------- iterator implementations ----------------

template <typename T>
typename SListCircularQT<T>::iterator& SListCircularQT<T>::iterator::operator++() 
{
    if (m_cur) 
    {
        m_cur = m_cur->m_next;
        ++m_traversed;
        if (m_traversed >= m_total) m_cur = nullptr;
    }
    return *this;
}

template <typename T>
typename SListCircularQT<T>::iterator SListCircularQT<T>::iterator::operator++(int) 
{
    iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T>
bool SListCircularQT<T>::iterator::operator==(const iterator& o) const 
{
    return m_cur == o.m_cur && m_traversed == o.m_traversed;
}

template <typename T>
bool SListCircularQT<T>::iterator::operator!=(const iterator& o) const 
{
    return !(*this == o);
}

template <typename T>
typename SListCircularQT<T>::const_iterator& SListCircularQT<T>::const_iterator::operator++() 
{
    if (m_cur) 
    {
        m_cur = m_cur->m_next;
        ++m_traversed;
        if (m_traversed >= m_total) m_cur = nullptr;
    }

    return *this;
}

template <typename T>
typename SListCircularQT<T>::const_iterator SListCircularQT<T>::const_iterator::operator++(int) 
{
    const_iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T>
bool SListCircularQT<T>::const_iterator::operator==(const const_iterator& o) const {
    return m_cur == o.m_cur && m_traversed == o.m_traversed;
}

template <typename T>
bool SListCircularQT<T>::const_iterator::operator!=(const const_iterator& o) const {
    return !(*this == o);
}
