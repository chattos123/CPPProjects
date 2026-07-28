/**
 * @file SMapDictionary.h
 * @brief Declares the SMapDictionary template class for a hash-map-based dictionary data structure.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"
#include "SPair.h"
#include <vector>
#include <list>
#include <functional> // std::hash

/**
 * @class SMapDictionary
 * @brief A generic key-value dictionary implemented using a hash table with separate chaining for collision resolution.
 * 
 * Uses `std::vector` of `std::list` buckets holding `SPair<K, V>` objects. Automatically resizes (rehashes) 
 * when the load factor exceeds capacity thresholds to maintain efficient lookups.
 *
 * @tparam K Type of keys stored in the dictionary. Must support `std::hash<K>` and `operator==`.
 * @tparam V Type of values associated with keys.
 */
template <typename K, typename V>
class SMapDictionary {
private:
    std::vector<std::list<SPair<K, V>>> m_buckets; ///< Buckets container using separate chaining for collision resolution.
    int m_size;                                    ///< Total number of key-value pairs stored in the dictionary.
    int m_capacity;                                ///< Current number of buckets in the hash table.

    /**
     * @brief Computes the bucket index for a given key using `std::hash`.
     *
     * @param[in] key Reference to the key to be hashed.
     * @return int Non-negative bucket index within the range [0, m_capacity - 1].
     * @remark Internal helper method for bucket selection.
     */
    int getBucketIndex(const K& key) const {
        return std::hash<K>{}(key) % m_capacity;
    }

    /**
     * @brief Rehashes the dictionary by doubling capacity and re-distributing existing entries.
     *
     * Invoked automatically when insertion causes the load factor to exceed the threshold limit.
     *
     * @param None
     * @return void
     * @remark Re-allocates internal bucket storage and re-calculates bucket indices for all active entries.
     */
    void rehash();

public:
    /**
     * @brief Constructs an empty SMapDictionary instance with a specified initial bucket capacity.
     *
     * @param[in] capacity Initial number of buckets for the underlying hash table (defaults to 8).
     */
    SMapDictionary(int capacity = 8);

    /**
     * @brief Inserts a key-value pair into the dictionary or updates value if key already exists.
     *
     * @param[in] key Key associated with the value to insert/update.
     * @param[in] value Value to associate with the given key.
     * @return void
     * @remark Triggers `rehash()` automatically if insertion exceeds load factor capacity.
     */
    void insert(const K& key, const V& value);

    /**
     * @brief Checks whether a specific key exists in the dictionary.
     *
     * @param[in] key Key to look up in the hash table.
     * @return true If the key exists within one of the buckets.
     * @return false If the key is not found.
     * @remark Average-case time complexity is O(1).
     */
    bool contains(const K& key) const;

    /**
     * @brief Retrieves a mutable reference to the value associated with the specified key.
     *
     * @param[in] key Key whose value is to be accessed.
     * @return V& Reference to the associated value stored in the dictionary.
     * @throws std::out_of_range If the specified key does not exist in the dictionary.
     * @remark Allows direct modification of the value stored under the key.
     */
    V& at(const K& key);

    /**
     * @brief Removes the key-value pair corresponding to the specified key from the dictionary.
     *
     * @param[in] key Key of the entry to be deleted.
     * @return void
     * @remark Decrements `m_size` upon successful deletion. No-op if key is not present.
     */
    void erase(const K& key);

    /**
     * @brief Displays all key-value pairs grouped by bucket indices to standard output.
     *
     * @param None
     * @return void
     * @remark Useful for debugging bucket distributions and inspecting collision patterns.
     */
    void display() const;
};

// Include template implementation definitions
#include "SMapDictionary.tpp"