template <typename T>
SListStackT<T>::SListStackT(const SListStackT& other) {
    // Copy elements from other list
    for (int i = 0; i < other.m_list.GetLength(); ++i) {
        auto node = other.m_list.GetElementAt(i);
        if (node) {
            m_list.AddElement(node->m_val);
        }
    }
}

template <typename T>
SListStackT<T>& SListStackT<T>::operator=(const SListStackT& other) {
    if (this == &other) return *this;

    // Clear current list
    while (!m_list.IsEmpty()) {
        m_list.DeleteElement();
    }

    // Copy elements from other
    for (int i = 0; i < other.m_list.GetLength(); ++i) {
        auto node = other.m_list.GetElementAt(i);
        if (node) {
            m_list.AddElement(node->m_val);
        }
    }

    return *this;
}

template <typename T>
void SListStackT<T>::push(const T& value) {
    m_list.AddHead(value);
}

template <typename T>
T SListStackT<T>::pop() {
    if (m_list.IsEmpty()) throw std::runtime_error("Stack underflow");
    T val = m_list.GetHead()->m_val;
    m_list.DeleteHead();
    return val;
}

template <typename T>
T SListStackT<T>::top() const 
{
    if (m_list.IsEmpty()) throw std::runtime_error("Stack is empty");
    return m_list.GetHead()->m_val;
}

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
