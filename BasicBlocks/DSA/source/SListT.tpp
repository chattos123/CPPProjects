/**
 * @file SListT.tpp
 * @brief Implementation details for the templated SListT class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include <iostream>

/**
 * @brief Constructs an empty SListT instance.
 *
 * Initializes the head pointer (`m_head`) to nullptr and sets element count (`m_count`) to 0.
 *
 * @tparam T Type of elements stored in the list.
 * @param None
 */
template <typename T>
SListT<T>::SListT() : m_head(nullptr), m_count(0) {}

/**
 * @brief Destructs the SListT instance and releases dynamic memory allocated for all nodes.
 *
 * Iteratively traverses the linked list from head to tail, deallocating each node to prevent memory leaks.
 *
 * @tparam T Type of elements stored in the list.
 * @param None
 */
template <typename T>
SListT<T>::~SListT() 
{
    while (m_head != nullptr) 
    {
        psNodeT<T> temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }

    m_count = 0;
}

/**
 * @brief Appends a new value to the end (tail) of the list.
 *
 * Allocates a new node and inserts it as the head if the list is empty, or appends it to the tail.
 *
 * @tparam T Type of element stored in the list.
 * @param[in] val Constant reference to the element value to append.
 * @return true If node allocation and insertion succeeded.
 * @return false If memory allocation for the new node failed.
 * @remark Increments `m_count` upon successful insertion.
 */
template <typename T>
bool SListT<T>::AddElement(const T& val) 
{
    psNodeT<T> newNode = new tagNodeT<T>{val, nullptr};
    if (!newNode) return false;

    if (!m_head) 
    {
        m_head = newNode;
    } 
    else 
    {
        psNodeT<T> last = GetLastElement();
        last->m_next = newNode;
    }

    ++m_count;
    return true;
}

/**
 * @brief Retrieves a pointer to the node at the specified zero-based index position.
 *
 * Sequentially traverses the list starting from `m_head`.
 *
 * @tparam T Type of element stored in the list.
 * @param[in] index Zero-based index position of the requested node.
 * @return psNodeT<T> Pointer to the target node if index is valid; nullptr if index is out of bounds.
 */
template <typename T>
psNodeT<T> SListT<T>::GetElementAt(int index) 
{
    if (index < 0 || index >= m_count) return nullptr;
    psNodeT<T> current = m_head;
    for (int i = 0; i < index; ++i) current = current->m_next;
    return current;
}

/**
 * @brief Retrieves a pointer to the last (tail) node in the list.
 *
 * Traverses along next-pointers until reaching the terminal node.
 *
 * @tparam T Type of element stored in the list.
 * @param None
 * @return psNodeT<T> Pointer to tail node; nullptr if the list is empty.
 */
template <typename T>
psNodeT<T> SListT<T>::GetLastElement() 
{
    if (!m_head) return nullptr;
    psNodeT<T> current = m_head;
    while (current->m_next) current = current->m_next;
    return current;
}

/**
 * @brief Removes and deallocates the last (tail) node from the list.
 *
 * @tparam T Type of element stored in the list.
 * @param None
 * @return true If the tail node was successfully deleted.
 * @return false If the list was empty.
 * @remark Decrements `m_count` on successful deletion.
 */
template <typename T>
bool SListT<T>::DeleteElement() 
{
    if (!m_head) return false;

    if (!m_head->m_next) 
    {
        delete m_head;
        m_head = nullptr;
    } 
    else 
    {
        psNodeT<T> prev = m_head;
        psNodeT<T> curr = m_head->m_next;

        while (curr->m_next) 
        {
            prev = curr;
            curr = curr->m_next;
        }
        prev->m_next = nullptr;
        delete curr;
    }
    --m_count;
    return true;
}

/**
 * @brief Prints list element contents sequentially to standard output.
 *
 * Formats element values as `E0=val1  E1=val2 ...`.
 *
 * @tparam T Type of element stored in the list.
 * @param None
 * @return true If traversal and output completed successfully.
 * @return false If the list was empty.
 * @remark Requires `operator<<` to be defined for type T.
 */
template <typename T>
bool SListT<T>::Display() 
{
    if (!m_head) 
    {
        std::cout << "List is empty\n";
        return false;
    }
    psNodeT<T> current = m_head;
    int idx = 0;

    while (current) 
    {
        std::cout << "E" << idx++ << "=" << current->m_val << "\t";
        current = current->m_next;
    }
    std::cout << "\n";
    return true;
}

/**
 * @brief Inserts a new element value immediately following the node at target position.
 *
 * @tparam T Type of element stored in the list.
 * @param[in] pos Zero-based position index after which the new value should be inserted.
 * @param[in] val Constant reference to the element value to insert.
 * @return true If insertion succeeded.
 * @return false If `pos` is out of bounds or node allocation failed.
 * @remark Increments `m_count` upon successful insertion.
 */
template <typename T>
bool SListT<T>::AddElementAfter(int pos, const T& val) 
{
    if (pos < 0 || pos >= m_count) return false;

    psNodeT<T> target = GetElementAt(pos);
    if (!target) return false;
    psNodeT<T> newNode = new tagNodeT<T>{val, target->m_next};
    target->m_next = newNode;
    ++m_count;
    return true;
}

/**
 * @brief Inserts a new element at the front (head) of the list.
 *
 * @tparam T Type of element stored in the list.
 * @param[in] val Constant reference to the element value to prepend.
 * @return true If head node insertion succeeded.
 * @return false If memory allocation failed.
 * @remark Operates with O(1) time complexity and increments `m_count`.
 */
template <typename T>
bool SListT<T>::AddHead(const T& val) 
{
    psNodeT<T> newNode = new sNodeT<T>{val, m_head};
    m_head = newNode;
    ++m_count;
    return true;
}

/**
 * @brief Removes the element at the front (head) of the list.
 *
 * @tparam T Type of element stored in the list.
 * @param None
 * @return true If the head node was successfully deleted.
 * @return false If the list was empty.
 * @remark Operates with O(1) time complexity and decrements `m_count`.
 */
template <typename T>
bool SListT<T>::DeleteHead() 
{
    if (!m_head) return false;

    psNodeT<T> temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    temp = nullptr;
    --m_count;
    return true;
}

/**
 * @brief Retrieves a const pointer to the current head node of the list.
 *
 * @tparam T Type of element stored in the list.
 * @param None
 * @return psNodeT<T> Pointer to head node; nullptr if the list is empty.
 * @remark Non-destructive getter method providing O(1) complexity.
 */
template <typename T>
psNodeT<T> SListT<T>::GetHead() const 
{
    return m_head;
}