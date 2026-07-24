/***********************************************************************
* File: SHashMap.tpp
* Description: Implements the templated SHashMap class functions.
***********************************************************************/

 /***********************************************************************
 * Function: SHashMap
 *
 * Input:
 *   - int capacity : Initial number of buckets
 *   - Hash h       : Hash functor (default std::hash<K>)
 *
 * Output:
 *   - Constructs an empty hash map with given capacity.
 *
 * Remarks:
 *   Initializes buckets as empty singly-linked lists.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
SHashMap<K,V,Hash>::SHashMap(int capacity, Hash h)
    : m_size(0), m_capacity(capacity), m_hasher(h) {
    m_buckets.reserve(m_capacity);
    for (int i = 0; i < m_capacity; ++i) {
        m_buckets.push_back(SListT<SPair<K,V>>());
    }
}

/***********************************************************************
 * Function: rehash
 *
 * Input:
 *   - None
 *
 * Output:
 *   - None
 *
 * Remarks:
 *   Doubles bucket capacity and redistributes all existing elements
 *   into new buckets based on updated hash indices.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
void SHashMap<K,V,Hash>::rehash() {
    int newCapacity = m_capacity * 2;
    SVectorT<SListT<SPair<K,V>>> newBuckets;
    newBuckets.reserve(newCapacity);
    for (int i = 0; i < newCapacity; ++i) {
        newBuckets.push_back(SListT<SPair<K,V>>());
    }

    for (int i = 0; i < m_capacity; ++i) {
        auto bucket = m_buckets[i];
        auto node = bucket.GetHead();
        while (node) {
            int newIndex = m_hasher(node->m_val.first) % newCapacity;
            newBuckets[newIndex].AddElement(node->m_val);
            node = node->m_next;
        }
    }

    m_buckets = std::move(newBuckets);
    m_capacity = newCapacity;
}

/***********************************************************************
 * Function: insert
 *
 * Input:
 *   - const K& key   : Key to insert
 *   - const V& value : Value to associate with key
 *
 * Output:
 *   - None
 *
 * Remarks:
 *   If key exists, updates its value. Otherwise, inserts new SPair.
 *   Triggers rehash if load factor exceeds 0.75.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
void SHashMap<K,V,Hash>::insert(const K& key, const V& value) {
    int index = getBucketIndex(key);
    auto& bucket = m_buckets[index];
    auto node = bucket.GetHead();
    while (node) {
        if (node->m_val.first == key) {
            node->m_val.second = value; // update
            return;
        }
        node = node->m_next;
    }
    bucket.AddElement(SPair<K,V>(key, value));
    ++m_size;

    if (m_size > m_capacity * 0.75) {
        rehash();
    }
}

/***********************************************************************
 * Function: contains
 *
 * Input:
 *   - const K& key : Key to search
 *
 * Output:
 *   - bool : True if key exists, false otherwise
 *
 * Remarks:
 *   Performs linear search within the bucket chain.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
bool SHashMap<K,V,Hash>::contains(const K& key) const {
    int index = getBucketIndex(key);
    auto node = m_buckets[index].GetHead();
    while (node) {
        if (node->m_val.first == key) return true;
        node = node->m_next;
    }
    return false;
}

/***********************************************************************
 * Function: at
 *
 * Input:
 *   - const K& key : Key to search
 *
 * Output:
 *   - V& : Reference to associated value
 *
 * Remarks:
 *   Throws std::out_of_range if key not found.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
V& SHashMap<K,V,Hash>::at(const K& key) {
    int index = getBucketIndex(key);
    auto node = m_buckets[index].GetHead();
    while (node) {
        if (node->m_val.first == key) return node->m_val.second;
        node = node->m_next;
    }
    throw std::out_of_range("Key not found");
}

/***********************************************************************
 * Function: erase
 *
 * Input:
 *   - const K& key : Key to remove
 *
 * Output:
 *   - None
 *
 * Remarks:
 *   Removes key–value pair if found. Adjusts linked list pointers.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
void SHashMap<K,V,Hash>::erase(const K& key) {
    int index = getBucketIndex(key);
    auto& bucket = m_buckets[index];
    auto node = bucket.GetHead();
    psNodeT<SPair<K,V>> prev = nullptr;
    while (node) {
        if (node->m_val.first == key) {
            if (prev) prev->m_next = node->m_next;
            else bucket.DeleteHead();
            --m_size;
            return;
        }
        prev = node;
        node = node->m_next;
    }
}

/***********************************************************************
 * Function: display
 *
 * Input:
 *   - None
 *
 * Output:
 *   - None
 *
 * Remarks:
 *   Prints all key–value pairs in the map to standard output.
 ***********************************************************************/
template <typename K, typename V, typename Hash>
void SHashMap<K,V,Hash>::display() const {
    std::cout << "{ ";
    for (int i = 0; i < m_capacity; ++i) {
        auto node = m_buckets[i].GetHead();
        while (node) {
            std::cout << node->m_val.first << ": " << node->m_val.second << ", ";
            node = node->m_next;
        }
    }
    std::cout << "}" << std::endl;
}
