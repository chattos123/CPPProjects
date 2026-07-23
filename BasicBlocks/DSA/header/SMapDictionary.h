/***********************************************************************
* File: SMapDictionary.h
* Description: Declares the templated SMapDictionary class for a type-safe
*              dictionary (key-value) container.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <stdexcept>
#include <utility>   // for std::pair

/***********************************************************************
* Class: SMapDictionary<K, V>
*
* Purpose: A generic dictionary container supporting insertion, lookup,
*          deletion, iteration, and basic element operations.
***********************************************************************/
template <typename K, typename V>
class DSALIB_API SMapDictionary {
private:
    std::pair<K, V>* m_data;
    int m_size;
    int m_capacity;

    void resize(int newCapacity);

public:
    using iterator = std::pair<K, V>*;
    using const_iterator = const std::pair<K, V>*;

    iterator begin() { return m_data; }
    iterator end() { return m_data + m_size; }
    const_iterator begin() const { return m_data; }
    const_iterator end() const { return m_data + m_size; }

    SMapDictionary();                          // default constructor
    ~SMapDictionary();                         // destructor
    SMapDictionary(const SMapDictionary& other); // copy constructor
    SMapDictionary(SMapDictionary&& other) noexcept; // move constructor
    SMapDictionary& operator=(const SMapDictionary& other); // copy assignment
    SMapDictionary& operator=(SMapDictionary&& other) noexcept; // move assignment

    void insert(const K& key, const V& value); // add key-value pair
    bool contains(const K& key) const;         // check if key exists
    V& at(const K& key);                       // access value by key
    const V& at(const K& key) const;           // const access
    void erase(const K& key);                  // remove key-value pair
    int size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void display() const;                      // print dictionary
};

// include template implementation
#include "SMapDictionary.tpp"
