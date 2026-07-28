/**
 * @file SListStackT.tpp
 * @brief Implementation details for the templated SListStackT class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SListStackT.h"

/**
 * @brief Copy constructor performing a deep copy of another SListStackT instance.
 *
 * Traverses the underlying linked list of the source stack and appends copies of each element
 * to reconstruct identical stack contents.
 *
 * @tparam T Type of elements stored within the stack.
 * @param[in] other Source SListStackT instance to copy.
 */
template <typename T>
SListStackT<T>::SListStackT(const SListStackT& other) 
{
    // Copy elements sequentially from source list
    for (int i = 0; i < other.m_list.GetLength(); ++i) 
    {
        auto node = other.m_list.GetElementAt(i);

        if (node) 
        {
            m_list.AddElement(node->m_val);
        }
    }
}

/**
 * @brief Copy assignment operator replacing stack contents with a deep copy of another SListStackT instance.
 *
 * Clears current stack contents before copying elements sequentially from the source stack instance.
 *
 * @tparam T Type of elements stored within the stack.
 * @param[in] other Source SListStackT instance to copy.
 * @return SListStackT<T>& Reference to this updated stack instance.
 * @remark Protects against self-assignment internally.
 */
template <typename T>
SListStackT<T>& SListStackT<T>::operator=(const SListStackT& other) 
{
    if (this == &other) return *this;

    // Clear current stack contents
    while (!m_list.IsEmpty()) 
    {
        m_list.DeleteElement();
    }

    // Copy elements sequentially from source
    for (int i = 0; i < other.m_list.GetLength(); ++i) 
    {
        auto node = other.m_list.GetElementAt(i);
        
        if (node) 
        {
            m_list.AddElement(node->m_val);
        }
    }

    return *this;
}

/**
 * @brief Pushes a new element onto the top of the stack.
 *
 * @tparam T Type of element stored in the stack.
 * @param[in] value Constant reference to the element value to push onto the stack.
 * @return void
 * @remark Inserts element at the head of the underlying linked list to achieve O(1) push complexity.
 */
template <typename T>
void SListStackT<T>::push(const T& value) 
{
    m_list.AddHead(value);
}

/**
 * @brief Removes and returns the element at the top of the stack.
 *
 * @tparam T Type of element stored in the stack.
 * @param None
 * @return T The element value previously residing at the top of the stack.
 * @throws std::runtime_error If invoked on an empty stack (`m_list.IsEmpty() == true`).
 * @remark Removes element from the head of the underlying linked list to achieve O(1) pop complexity.
 */
template <typename T>
T SListStackT<T>::pop() 
{
    if (m_list.IsEmpty()) throw std::runtime_error("Stack underflow");
    T val = m_list.GetHead()->m_val;
    m_list.DeleteHead();
    return val;
}

/**
 * @brief Accesses the element currently residing at the top of the stack without removing it.
 *
 * @tparam T Type of element stored in the stack.
 * @param None
 * @return T Copy of the top element value.
 * @throws std::runtime_error If invoked on an empty stack (`m_list.IsEmpty() == true`).
 * @remark Non-destructive inspection method.
 */
template <typename T>
T SListStackT<T>::top() const 
{
    if (m_list.IsEmpty()) throw std::runtime_error("Stack is empty");
    return m_list.GetHead()->m_val;
}

/**
 * @brief Prints the contents of the stack from top to bottom to standard output.
 *
 * @tparam T Type of element stored in the stack.
 * @param None
 * @return void
 * @remark Non-destructive traversal output. Requires `operator<<` to be defined for type T.
 */
template <typename T>
void SListStackT<T>::display() const 
{
    if (m_list.IsEmpty()) {
        std::cout << "Stack is empty\n";
        return;
    }
    std::cout << "Stack contents (top to bottom):\n";
    auto node = m_list.GetHead();
    while (node) {
        std::cout << node->m_val << "\n";
        node = node->m_next;
    }
}