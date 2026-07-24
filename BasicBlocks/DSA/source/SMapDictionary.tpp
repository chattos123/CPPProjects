template <typename K, typename V>
SMapDictionary<K,V>::SMapDictionary(int capacity)
    : m_size(0), m_capacity(capacity), m_buckets(capacity) {}

template <typename K, typename V>
void SMapDictionary<K,V>::rehash() {
    int newCapacity = m_capacity * 2;
    std::vector<std::list<SPair<K,V>>> newBuckets(newCapacity);

    for (auto& bucket : m_buckets) {
        for (auto& kv : bucket) {
            int newIndex = std::hash<K>{}(kv.first) % newCapacity;
            newBuckets[newIndex].push_back(kv);
        }
    }

    m_buckets.swap(newBuckets);
    m_capacity = newCapacity;
}

template <typename K, typename V>
void SMapDictionary<K,V>::insert(const K& key, const V& value) {
    int index = getBucketIndex(key);
    for (auto& kv : m_buckets[index]) {
        if (kv.first == key) {
            kv.second = value; // update existing
            return;
        }
    }
    m_buckets[index].push_back(SPair<K,V>(key, value));
    ++m_size;

    if (m_size > m_capacity * 0.75) { // load factor threshold
        rehash();
    }
}

template <typename K, typename V>
bool SMapDictionary<K,V>::contains(const K& key) const {
    int index = getBucketIndex(key);
    for (auto& kv : m_buckets[index]) {
        if (kv.first == key) return true;
    }
    return false;
}

template <typename K, typename V>
V& SMapDictionary<K,V>::at(const K& key) {
    int index = getBucketIndex(key);
    for (auto& kv : m_buckets[index]) {
        if (kv.first == key) return kv.second;
    }
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
void SMapDictionary<K,V>::erase(const K& key) {
    int index = getBucketIndex(key);
    for (auto it = m_buckets[index].begin(); it != m_buckets[index].end(); ++it) {
        if (it->first == key) {
            m_buckets[index].erase(it);
            --m_size;
            return;
        }
    }
}

template <typename K, typename V>
void SMapDictionary<K,V>::display() const {
    std::cout << "{ ";
    for (int i = 0; i < m_capacity; ++i) {
        for (auto& kv : m_buckets[i]) {
            std::cout << kv.first << ": " << kv.second << ", ";
        }
    }
    std::cout << "}" << std::endl;
}
