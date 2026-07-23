template <typename K, typename V>
SMapDictionary<K,V>::SMapDictionary() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename K, typename V>
SMapDictionary<K,V>::~SMapDictionary()
{
    delete[] m_data;
    m_data = nullptr;
}

template <typename K, typename V>
SMapDictionary<K,V>::SMapDictionary(const SMapDictionary& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new std::pair<K,V>[m_capacity];

    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

template <typename K, typename V>
SMapDictionary<K,V>& SMapDictionary<K,V>::operator=(const SMapDictionary& other)
 {
    if (this == &other) return *this;

    delete[] m_data;
    m_data =  nullptr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new std::pair<K,V>[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
    return *this;
}

template <typename K, typename V>
SMapDictionary<K,V>::SMapDictionary(SMapDictionary&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) 
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template <typename K, typename V>
SMapDictionary<K,V>& SMapDictionary<K,V>::operator=(SMapDictionary&& other) noexcept 
{
    if (this == &other) return *this;
    delete[] m_data;
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    return *this;
}

template <typename K, typename V>
void SMapDictionary<K,V>::resize(int newCapacity) 
{
    std::pair<K,V>* newData = new std::pair<K,V>[newCapacity];
    
    for (int i = 0; i < m_size; ++i)
    {
        newData[i] = m_data[i];
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

template <typename K, typename V>
void SMapDictionary<K,V>::insert(const K& key, const V& value)
{
    if (contains(key)) 
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_data[i].first == key) 
            {
                m_data[i].second = value;
                return;
            }
        }
    }

    if (m_size == m_capacity)
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        resize(newCapacity);
    }

    m_data[m_size++] = std::make_pair(key, value);
}

template <typename K, typename V>
bool SMapDictionary<K,V>::contains(const K& key) const
{
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i].first == key) return true;
    }
    return false;
}

template <typename K, typename V>
V& SMapDictionary<K,V>::at(const K& key) {
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i].first == key) return m_data[i].second;
    }
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
const V& SMapDictionary<K,V>::at(const K& key) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i].first == key) return m_data[i].second;
    }
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
void SMapDictionary<K,V>::erase(const K& key) {
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i].first == key) {
            for (int j = i; j < m_size - 1; ++j) {
                m_data[j] = m_data[j+1];
            }
            --m_size;
            return;
        }
    }
}

template <typename K, typename V>
void SMapDictionary<K,V>::display() const {
    std::cout << "{ ";
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_data[i].first << ": " << m_data[i].second;
        if (i < m_size - 1) std::cout << ", ";
    }
    std::cout << " }" << std::endl;
}
