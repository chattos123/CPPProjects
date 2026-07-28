/**
 * @file SHashMap.tpp
 * @brief Implementation details for the templated SHashMap class member functions.
 * @author Soumyajit C
 * @date 2026
 */

#include "SHashMap.h"

/**
 * @brief Constructs an empty SHashMap instance with specified initial bucket capacity and hash functor.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param[in] capacity Initial bucket count for allocation.
 * @param[in] h Functor object used for key hashing.
 * @remark Reserves bucket array memory and initializes empty singly-linked list instances.
 */
template <typename K, typename V, typename Hash>
SHashMap<K, V, Hash>::SHashMap(int capacity, Hash h)
    : m_size(0), m_capacity(capacity), m_hasher(h) 
{
    m_buckets.reserve(m_capacity);

    for (int i = 0; i < m_capacity; ++i) 
    {
        m_buckets.push_back(SListT<SPair<K, V>>());
    }
}

/**
 * @brief Reallocates and doubles the bucket array capacity, re-hashing all existing key-value pairs.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param None
 * @return void
 * @remark Triggered internally when the load factor exceeds 0.75. Redistributes nodes across expanded buckets.
 */
template <typename K, typename V, typename Hash>
void SHashMap<K, V, Hash>::rehash() 
{
    int newCapacity = m_capacity * 2;
    SVectorT<SListT<SPair<K, V>>> newBuckets;
    newBuckets.reserve(newCapacity);

    for (int i = 0; i < newCapacity; ++i) 
    {
        newBuckets.push_back(SListT<SPair<K, V>>());
    }

    for (int i = 0; i < m_capacity; ++i) 
    {
        auto& bucket = m_buckets[i];
        auto node = bucket.GetHead();

        while (node) 
        {
            int newIndex = m_hasher(node->m_val.first) % newCapacity;
            newBuckets[newIndex].AddElement(node->m_val);
            node = node->m_next;
        }
    }

    m_buckets = std::move(newBuckets);
    m_capacity = newCapacity;
}

/**
 * @brief Inserts a key-value pair into the map or updates the mapped value if the key already exists.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param[in] key Key to insert or update.
 * @param[in] value Value to associate with the given key.
 * @return void
 * @remark Automatically invokes `rehash()` if total elements exceed 75% of capacity (`m_size > m_capacity * 0.75`).
 */
template <typename K, typename V, typename Hash>
void SHashMap<K, V, Hash>::insert(const K& key, const V& value) 
{
    int index = getBucketIndex(key);
    auto& bucket = m_buckets[index];
    auto node = bucket.GetHead();

    while (node) 
    {
        if (node->m_val.first == key) 
        {
            node->m_val.second = value; // update existing value
            return;
        }

        node = node->m_next;
    }
    bucket.AddElement(SPair<K, V>(key, value));
    ++m_size;

    if (m_size > m_capacity * 0.75) {
        rehash();
    }
}

/**
 * @brief Checks whether a specified key exists in the hash map.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param[in] key Key to look up in the map.
 * @return true If key exists within target bucket collision list.
 * @return false If key is not found.
 * @remark Performs linear traversal along the target bucket's collision chain.
 */
template <typename K, typename V, typename Hash>
bool SHashMap<K, V, Hash>::contains(const K& key) const 
{
    int index = getBucketIndex(key);
    auto node = m_buckets[index].GetHead();

    while (node) 
    {
        if (node->m_val.first == key) return true;
        node = node->m_next;
    }

    return false;
}

/**
 * @brief Retrieves a mutable reference to the value associated with the specified key.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param[in] key Key whose associated value is to be accessed.
 * @return V& Mutable reference to mapped value.
 * @throws std::out_of_range If the key does not exist in the map.
 */
template <typename K, typename V, typename Hash>
V& SHashMap<K, V, Hash>::at(const K& key) 
{
    int index = getBucketIndex(key);
    auto node = m_buckets[index].GetHead();

    while (node) 
    {
        if (node->m_val.first == key) return node->m_val.second;
        node = node->m_next;
    }
    throw std::out_of_range("Key not found");
}

/**
 * @brief Removes the key-value pair corresponding to the specified key from the hash map.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param[in] key Key of the entry to be deleted.
 * @return void
 * @remark Unlinks the matching node from the collision chain and decrements `m_size`. No-op if key is not found.
 */
template <typename K, typename V, typename Hash>
void SHashMap<K, V, Hash>::erase(const K& key) 
{
    int index = getBucketIndex(key);
    auto& bucket = m_buckets[index];
    auto node = bucket.GetHead();
    psNodeT<SPair<K, V>> prev = nullptr;

    while (node) 
    {
        if (node->m_val.first == key) 
        {
            if (prev) 
            {
                prev->m_next = node->m_next;
                // fix memory leak..else block is deleteng the node 
                // but if block was not.
                delete node;
                node = nullptr;
            } 
            else 
            {
                bucket.DeleteHead();
            }

            --m_size;
            return;
        }
        prev = node;
        node = node->m_next;
    }
}

/**
 * @brief Prints all key-value pairs stored across all buckets to standard output.
 *
 * @tparam K Key type.
 * @tparam V Value type.
 * @tparam Hash Hash functor type.
 * @param None
 * @return void
 * @remark Formatted output stream representation formatted as `{ key1: val1, key2: val2, }`.
 */
template <typename K, typename V, typename Hash>
void SHashMap<K, V, Hash>::display() const 
{
    std::cout << "{ ";

    for (int i = 0; i < m_capacity; ++i) 
    {
        auto node = m_buckets[i].GetHead();
        while (node) 
        {
            std::cout << node->m_val.first << ": " << node->m_val.second << ", ";
            node = node->m_next;
        }
    }

    std::cout << "}" << std::endl;
}