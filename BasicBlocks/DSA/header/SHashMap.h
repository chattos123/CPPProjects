/***********************************************************************
* File: SHashMap.h
* Description: Declares the templated SHashMap class for a type-safe
*              hash-based dictionary container using SPair, SVectorT,
*              and SListT for bucket storage.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include "SPair.h"
#include "SVectorT.h"
#include "SListT.h"
#include <functional> // std::hash
#include <iostream>
#include <stdexcept>

/***********************************************************************
* Class: SHashMap<K,V,Hash>
*
* Purpose: Provides a generic hash map container supporting insertion,
*          lookup, deletion, and display of key–value pairs. Uses
*          SPair<K,V> for storage, SVectorT for buckets, and SListT
*          for collision handling via separate chaining.
***********************************************************************/
template <typename K, typename V, typename Hash = std::hash<K>>
class DSALIB_API SHashMap {
private:
    SVectorT<SListT<SPair<K,V>>> m_buckets;  ///< Buckets array
    int m_size;                              ///< Number of elements
    int m_capacity;                          ///< Current bucket capacity
    Hash m_hasher;                           ///< Hash functor

    /***********************************************************************
    * Function: getBucketIndex
    *
    * \brief Computes the bucket index for a given key using the hash functor.
    ***********************************************************************/
    int getBucketIndex(const K& key) const {
        return m_hasher(key) % m_capacity;
    }

    /***********************************************************************
    * Function: rehash
    *
    * \brief Doubles the bucket capacity and redistributes elements.
    ***********************************************************************/
    void rehash();

public:
    /***********************************************************************
    * Function: SHashMap
    *
    * \brief Constructs a hash map with an initial capacity and optional
    *        custom hash functor.
    ***********************************************************************/
    SHashMap(int capacity = 8, Hash h = Hash());

    /***********************************************************************
    * Function: insert
    *
    * \brief Inserts a key–value pair into the map. Updates value if key exists.
    ***********************************************************************/
    void insert(const K& key, const V& value);

    /***********************************************************************
    * Function: contains
    *
    * \brief Checks if the given key exists in the map.
    ***********************************************************************/
    bool contains(const K& key) const;

    /***********************************************************************
    * Function: at
    *
    * \brief Returns a reference to the value associated with the key.
    *        Throws std::out_of_range if key not found.
    ***********************************************************************/
    V& at(const K& key);

    /***********************************************************************
    * Function: erase
    *
    * \brief Removes the key–value pair associated with the given key.
    ***********************************************************************/
    void erase(const K& key);

    /***********************************************************************
    * Function: display
    *
    * \brief Prints all key–value pairs in the map to standard output.
    ***********************************************************************/
    void display() const;

    /***********************************************************************
    * Function: size
    *
    * \brief Returns the number of elements in the map.
    ***********************************************************************/
    int size() const { return m_size; }

    /***********************************************************************
    * Function: empty
    *
    * \brief Returns true if the map contains no elements.
    ***********************************************************************/
    bool empty() const { return m_size == 0; }
};

// include template implementation
#include "SHashMap.tpp"
