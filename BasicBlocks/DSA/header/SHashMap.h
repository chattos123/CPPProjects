/**
 * @file SHashMap.h
 * @brief Declares the templated SHashMap class for a type-safe hash-based dictionary container.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

#include "SPair.h"
#include "SVectorT.h"
#include "SListT.h"
#include <functional> // std::hash
#include <iostream>
#include <stdexcept>

/**
 * @class SHashMap
 * @brief A generic hash map container supporting key-value pair insertion, lookup, removal, and bucket inspection.
 * 
 * Employs `SPair<K, V>` for key-value pair storage, `SVectorT` for internal bucket array management, 
 * and `SListT` for separate chaining collision resolution.
 *
 * @tparam K Type of keys stored in the map. Must support equality comparison (`operator==`).
 * @tparam V Type of values mapped to keys.
 * @tparam Hash Functor type generating hash codes for keys (defaults to `std::hash<K>`).
 */
template <typename K, typename V, typename Hash = std::hash<K>>
class SHashMap {
private:
    SVectorT<SListT<SPair<K, V>>> m_buckets; ///< Dynamic array of singly-linked lists serving as hash buckets.
    int m_size;                              ///< Total number of active key-value pairs stored in the hash map.
    int m_capacity;                          ///< Current number of buckets in the map.
    Hash m_hasher;                           ///< Instance of the hash functor used for key hashing.

    /**
     * @brief Computes the target bucket array index for a given key using the hash functor.
     *
     * @param[in] key Reference to the key whose bucket index is to be computed.
     * @return int Non-negative bucket index bounded within `[0, m_capacity - 1]`.
     * @remark Internal helper method for bucket selection.
     */
    int getBucketIndex(const K& key) const {
        return m_hasher(key) % m_capacity;
    }

    /**
     * @brief Reallocates and doubles the bucket capacity, redistributing all existing elements.
     *
     * Invoked automatically when insertion causes the load factor to exceed the allowable threshold.
     *
     * @param None
     * @return void
     * @remark Re-allocates internal bucket arrays and recalculates bucket indices for all entries.
     */
    void rehash();

public:
    /**
     * @brief Constructs an empty SHashMap instance with an initial bucket capacity and an optional hash functor.
     *
     * @param[in] capacity Initial bucket count (defaults to 8).
     * @param[in] h Functor object used for key hashing (defaults to `Hash()`).
     */
    SHashMap(int capacity = 8, Hash h = Hash());

    /**
     * @brief Inserts a key-value pair into the map or updates the value if the key already exists.
     *
     * @param[in] key Key to insert or update.
     * @param[in] value Value associated with the given key.
     * @return void
     * @remark Automatically triggers `rehash()` if the load factor exceeds capacity limits.
     */
    void insert(const K& key, const V& value);

    /**
     * @brief Checks whether a specified key exists in the map.
     *
     * @param[in] key Key to search for in the hash map.
     * @return true If the key exists within one of the collision chains.
     * @return false If the key is not found.
     * @remark Average time complexity is O(1).
     */
    bool contains(const K& key) const;

    /**
     * @brief Retrieves a mutable reference to the value associated with the specified key.
     *
     * @param[in] key Key whose mapped value is to be accessed.
     * @return V& Mutable reference to the mapped value.
     * @throws std::out_of_range If the key does not exist in the map.
     * @remark Allows in-place modification of mapped values.
     */
    V& at(const K& key);

    /**
     * @brief Removes the key-value pair associated with the specified key from the map.
     *
     * @param[in] key Key of the entry to remove.
     * @return void
     * @remark Decrements `m_size` upon successful deletion. No-op if the key is not found.
     */
    void erase(const K& key);

    /**
     * @brief Outputs all key-value pairs stored in the map to standard output.
     *
     * @param None
     * @return void
     * @remark Non-destructive display operation. Requires `operator<<` to be defined for `K` and `V`.
     */
    void display() const;

    /**
     * @brief Retrieves the total number of key-value pairs stored in the map.
     *
     * @param None
     * @return int Total element count.
     * @remark Inline query method providing O(1) time complexity.
     */
    int size() const { return m_size; }

    /**
     * @brief Checks whether the map contains no elements.
     *
     * @param None
     * @return true If `m_size == 0`.
     * @return false If the map contains one or more key-value pairs.
     * @remark Inline query method providing O(1) time complexity.
     */
    bool empty() const { return m_size == 0; }
};

// Include template implementation definitions
#include "SHashMap.tpp"