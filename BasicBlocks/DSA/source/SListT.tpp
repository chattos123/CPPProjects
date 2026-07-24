#include <iostream>

template <typename T>
/***********************************************************************/
/// <b>Function: SListT</b>
///
/// <b>remarks</b>    Initializes an empty templated linked list.
///
/***********************************************************************/
SListT<T>::SListT() : m_head(nullptr), m_count(0) {}

template <typename T>
/***********************************************************************/
/// <b>Function: ~SListT</b>
///
/// <b>remarks</b>    Releases all nodes in the templated linked list.
///
/***********************************************************************/
SListT<T>::~SListT() {
    while (m_head != nullptr) {
        psNodeT<T> temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }
    m_count = 0;
}

template <typename T>
/***********************************************************************/
/// <b>Function: AddElement</b>
///
/// <b>brief</b>      Appends a value to the end of the templated list.
///
/// <b>return</b>     bool True on success.
///
/***********************************************************************/
bool SListT<T>::AddElement(const T& val) {
    psNodeT<T> newNode = new tagNodeT<T>{val, nullptr};
    if (!newNode) return false;

    if (!m_head) {
        m_head = newNode;
    } else {
        psNodeT<T> last = GetLastElement();
        last->m_next = newNode;
    }
    ++m_count;
    return true;
}

template <typename T>
/***********************************************************************/
/// <b>Function: GetElementAt</b>
///
/// <b>brief</b>      Returns the node at the specified index.
///
/// <b>return</b>     psNodeT<T> pointer to the node, or nullptr if out of range.
///
/***********************************************************************/
psNodeT<T> SListT<T>::GetElementAt(int index) {
    if (index < 0 || index >= m_count) return nullptr;
    psNodeT<T> current = m_head;
    for (int i = 0; i < index; ++i) current = current->m_next;
    return current;
}

template <typename T>
/***********************************************************************/
/// <b>Function: GetLastElement</b>
///
/// <b>brief</b>      Returns the last node in the templated linked list.
///
/// <b>return</b>     psNodeT<T> pointer to the last node, or nullptr if empty.
///
/***********************************************************************/
psNodeT<T> SListT<T>::GetLastElement() {
    if (!m_head) return nullptr;
    psNodeT<T> current = m_head;
    while (current->m_next) current = current->m_next;
    return current;
}

template <typename T>
/***********************************************************************/
/// <b>Function: DeleteElement</b>
///
/// <b>brief</b>      Removes the last node from the templated list.
///
/// <b>return</b>     bool True if a node was removed.
///
/***********************************************************************/
bool SListT<T>::DeleteElement() {
    if (!m_head) return false;
    if (!m_head->m_next) {
        delete m_head;
        m_head = nullptr;
    } else {
        psNodeT<T> prev = m_head;
        psNodeT<T> curr = m_head->m_next;
        while (curr->m_next) {
            prev = curr;
            curr = curr->m_next;
        }
        prev->m_next = nullptr;
        delete curr;
    }
    --m_count;
    return true;
}

template <typename T>
/***********************************************************************/
/// <b>Function: Display</b>
///
/// <b>brief</b>      Prints list contents to standard output.
///
/// <b>return</b>     bool True when the list is non-empty.
///
/***********************************************************************/
bool SListT<T>::Display() {
    if (!m_head) {
        std::cout << "List is empty\n";
        return false;
    }
    psNodeT<T> current = m_head;
    int idx = 0;
    while (current) {
        std::cout << "E" << idx++ << "=" << current->m_val << "\t";
        current = current->m_next;
    }
    std::cout << "\n";
    return true;
}

template <typename T>
/***********************************************************************/
/// <b>Function: AddElementAfter</b>
///
/// <b>brief</b>      Inserts a value after the specified element index.
///
/// <b>return</b>     bool True on success.
///
/***********************************************************************/
bool SListT<T>::AddElementAfter(int pos, const T& val) {
    if (pos < 0 || pos >= m_count) return false;
    psNodeT<T> target = GetElementAt(pos);
    if (!target) return false;
    psNodeT<T> newNode = new tagNodeT<T>{val, target->m_next};
    target->m_next = newNode;
    ++m_count;
    return true;
}

template <typename T>
bool SListT<T>::AddHead(const T& val) {
    psNodeT<T> newNode = new sNodeT<T>{val, m_head};
    m_head = newNode;
    ++m_count;
    return true;
}

template <typename T>
bool SListT<T>::DeleteHead() {
    if (!m_head) return false;
    psNodeT<T> temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    --m_count;
    return true;
}

template <typename T>
psNodeT<T> SListT<T>::GetHead() const {
    return m_head;
}

