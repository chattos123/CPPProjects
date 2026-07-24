#include "SPair.h"
#include <vector>
#include <list>
#include <functional> // std::hash

template <typename K, typename V>
class DSALIB_API SMapDictionary {
private:
    std::vector<std::list<SPair<K,V>>> m_buckets;
    int m_size;
    int m_capacity;

    int getBucketIndex(const K& key) const {
        return std::hash<K>{}(key) % m_capacity;
    }

    void rehash();

public:
    SMapDictionary(int capacity = 8);   // default capacity
    void insert(const K& key, const V& value);
    bool contains(const K& key) const;
    V& at(const K& key);
    void erase(const K& key);
    void display() const;
};

#include "SMapDictionary.tpp"
