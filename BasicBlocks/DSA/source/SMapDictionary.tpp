/**
 * @file SMapDictionary.tpp
 * @brief Implementation details for the templated SMapDictionary class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SMapDictionary.h"

/**
 * @brief Constructs an empty SMapDictionary instance with a specified initial capacity.
 *
 * Initializes size to 0 and pre-allocates the vector of bucket lists to the requested capacity.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param[in] capacity Initial bucket count for allocation (defaults to 8).
 */
template <typename K, typename V>
SMapDictionary<K, V>::SMapDictionary(int capacity)
    : m_size(0), m_capacity(capacity), m_buckets(capacity) {}

/**
 * @brief Reallocates and doubles the bucket array capacity, re-hashing all existing key-value pairs.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param None
 * @return void
 * @remark Triggered internally when the load factor exceeds 0.75 (`m_size > m_capacity * 0.75`).
 */
template <typename K, typename V>
void SMapDictionary<K, V>::rehash() 
{
    int newCapacity = m_capacity * 2;
    std::vector<std::list<SPair<K, V>>> newBuckets(newCapacity);

    for (auto& bucket : m_buckets) {
        for (auto& kv : bucket) {
            int newIndex = std::hash<K>{}(kv.first) % newCapacity;
            newBuckets[newIndex].push_back(kv);
        }
    }

    m_buckets.swap(newBuckets);
    m_capacity = newCapacity;
}

/**
 * @brief Inserts a key-value pair into the dictionary or updates the mapped value if the key already exists.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param[in] key Key to insert or update.
 * @param[in] value Value to associate with the given key.
 * @return void
 * @remark Automatically triggers `rehash()` if total elements exceed 75% of current bucket capacity.
 */
template <typename K, typename V>
void SMapDictionary<K, V>::insert(const K& key, const V& value) 
{
    int index = getBucketIndex(key);
    for (auto& kv : m_buckets[index]) {
        if (kv.first == key) {
            kv.second = value; // update existing value
            return;
        }
    }
    m_buckets[index].push_back(SPair<K, V>(key, value));
    ++m_size;

    if (m_size > m_capacity * 0.75) { // load factor threshold
        rehash();
    }
}

/**
 * @brief Checks whether a specified key exists in the dictionary.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param[in] key Key to look up in the hash table.
 * @return true If key exists within target bucket list.
 * @return false If key is not found.
 * @remark Performs linear traversal along the target bucket's linked list.
 */
template <typename K, typename V>
bool SMapDictionary<K, V>::contains(const K& key) const 
{
    int index = getBucketIndex(key);

    for (auto& kv : m_buckets[index]) 
    {
        if (kv.first == key) return true;
    }

    return false;
}

/**
 * @brief Retrieves a mutable reference to the value associated with the specified key.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param[in] key Key whose associated value is to be accessed.
 * @return V& Mutable reference to mapped value.
 * @throws std::out_of_range If the key does not exist in the dictionary.
 */
template <typename K, typename V>
V& SMapDictionary<K, V>::at(const K& key) 
{
    int index = getBucketIndex(key);

    for (auto& kv : m_buckets[index]) 
    {
        if (kv.first == key) return kv.second;
    }
    throw std::out_of_range("Key not found");
}

/**
 * @brief Removes the key-value pair corresponding to the specified key from the dictionary.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param[in] key Key of the entry to be deleted.
 * @return void
 * @remark Erases entry from target bucket list and decrements `m_size`. No-op if key is not found.
 */
template <typename K, typename V>
void SMapDictionary<K, V>::erase(const K& key) 
{
    int index = getBucketIndex(key);

    for (auto it = m_buckets[index].begin(); it != m_buckets[index].end(); ++it) 
    {
        if (it->first == key) 
        {
            m_buckets[index].erase(it);
            --m_size;
            return;
        }
    }
}

/**
 * @brief Outputs all key-value pairs stored across all buckets to standard output.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @param None
 * @return void
 * @remark Non-destructive display method formatted as `{ key1: val1, key2: val2, }`.
 */
template <typename K, typename V>
void SMapDictionary<K, V>::display() const 
{
    std::cout << "{ ";

    for (int i = 0; i < m_capacity; ++i) 
    {
        for (auto& kv : m_buckets[i]) 
        {
            std::cout << kv.first << ": " << kv.second << ", ";
        }
    }
    std::cout << "}" << std::endl;
}