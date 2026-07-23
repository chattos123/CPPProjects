# Detailed Design Document: `SHashMap<K, V, Hash>`

---

## 1. Class Overview & Architectural Goals

The `SHashMap<K, V, Hash>` class is a type-safe, generic dictionary (associative container) designed to store unique key–value pairs [cite: 2]. It provides average $O(1)$ time complexity for core operations such as insertion, lookup, and deletion [cite: 2].

### Key Architectural Characteristics
* **Collision Resolution:** **Separate Chaining** utilizing custom singly-linked lists (`SListT`) [cite: 2].
* **Underlying Storage:** Dynamic array of bucket lists managed via custom dynamic array class `SVectorT` [cite: 2].
* **Data Representation:** Individual key–value entries are encapsulated in `SPair<K, V>` [cite: 2].
* **Hashing Strategy:** Configurable hash functor with a default fallback to `std::hash<K>` [cite: 2].
* **Dynamic Resizing:** Automatic array doubling (rehashing) when the load factor exceeds $0.75$ [cite: 2].

---

## 2. Component Collaboration & Dependencies

```
+-----------------------------------------------------------------------+
|                            SHashMap<K, V, Hash>                       |
+-----------------------------------------------------------------------+
                                   |
            +----------------------+----------------------+
            | 1:N                                         | 1:1
            v                                             v
+-----------------------+                         +---------------------+
| SVectorT<SListT<...>> |                         |    Hash Functor     |
+-----------------------+                         +---------------------+
            |
            | Contains Buckets
            v
+-----------------------+
|   SListT<SPair<K,V>>  |
+-----------------------+
            |
            | Node Value
            v
+-----------------------+
|     SPair<K, V>       |
|  - first  : Key (K)   |
|  - second : Value (V) |
+-----------------------+
```

---

## 3. Class Diagram & Member Specifications

### 3.1 Private Data Members

| Member Name | Data Type | Description |
| :--- | :--- | :--- |
| `m_buckets` | `SVectorT<SListT<SPair<K,V>>>` | Array of bucket chains (singly-linked lists) [cite: 2]. |
| `m_size` | `int` | Total count of active key–value pairs stored in the map [cite: 2]. |
| `m_capacity` | `int` | Current total number of bucket slots allocated in `m_buckets` [cite: 2]. |
| `m_hasher` | `Hash` | Instantiated functor used to map keys to integer hash codes [cite: 2]. |

---

### 3.2 Private Helper Methods

#### `int getBucketIndex(const K& key) const`
* **Purpose:** Computes the array index in `m_buckets` for a given key [cite: 2].
* **Logic:** Computes `m_hasher(key) % m_capacity` [cite: 2].
* **Time Complexity:** $O(1)$ (assuming functor hash computation is $O(1)$).

#### `void rehash()`
* **Purpose:** Expands storage when capacity thresholds are reached to maintain $O(1)$ operational efficiency [cite: 2].
* **Algorithmic Steps:**
  1. Calculate `newCapacity = m_capacity * 2` [cite: 2].
  2. Instantiate a temporary `SVectorT<SListT<SPair<K,V>>>` named `newBuckets` initialized with `newCapacity` empty lists [cite: 2].
  3. Iterate through all lists in `m_buckets` from index $0$ to `m_capacity - 1` [cite: 2].
  4. Traverse each node in every list, recalculating the destination bucket:
     $$\text{newIndex} = \text{m\_hasher}(\text{node->m\_val.first}) \pmod{\text{newCapacity}}$$ [cite: 2]
  5. Add `node->m_val` into `newBuckets[newIndex]` [cite: 2].
  6. Transfer `newBuckets` ownership into `m_buckets` via `std::move` [cite: 2].
  7. Update `m_capacity` to `newCapacity` [cite: 2].

---

## 4. Public API Design & Operation Logic

### 4.1 Constructors

```cpp
SHashMap(int capacity = 8, Hash h = Hash());
```
* **Description:** Constructs an empty map instance [cite: 2].
* **Pre-conditions:** `capacity > 0`.
* **Post-conditions:** `m_size == 0`, `m_capacity` is set to user argument (or default 8), `m_buckets` is pre-allocated with `capacity` empty `SListT` chains [cite: 2].

---

### 4.2 Core Operations

#### `void insert(const K& key, const V& value)`
* **Description:** Inserts a key–value pair or updates the existing value if the key is already present [cite: 2].
* **Control Flow:**
  1. Determine `index = getBucketIndex(key)` [cite: 2].
  2. Perform linear traversal across `m_buckets[index]` [cite: 2].
  3. **If key matches (`node->m_val.first == key`):** Update `node->m_val.second = value` and return [cite: 2].
  4. **If key is missing:** Append `SPair<K, V>(key, value)` to `m_buckets[index]`, increment `m_size` [cite: 2].
  5. Check load factor condition:
     $$\text{if } (\text{m\_size} > \text{m\_capacity} \times 0.75) \implies \text{rehash}()$$ [cite: 2]

#### `bool contains(const K& key) const`
* **Description:** Queries presence of a key [cite: 2].
* **Control Flow:**
  1. Calculate `index = getBucketIndex(key)` [cite: 2].
  2. Traverse `m_buckets[index]` sequentially [cite: 2].
  3. Return `true` if matching key found; otherwise, return `false` [cite: 2].

#### `V& at(const K& key)`
* **Description:** Retrieves mutable reference to value associated with key [cite: 2].
* **Control Flow:**
  1. Locate target bucket `index = getBucketIndex(key)` [cite: 2].
  2. Traverse nodes; return reference `node->m_val.second` on match [cite: 2].
  3. Throw `std::out_of_range("Key not found")` if traversal completes without match [cite: 2].

#### `void erase(const K& key)`
* **Description:** Removes entry matching the specified key [cite: 2].
* **Control Flow:**
  1. Locate target bucket `index = getBucketIndex(key)` [cite: 2].
  2. Traverse chain tracking previous pointer `prev` and current pointer `node` [cite: 2].
  3. On match:
     * If `prev` exists: set `prev->m_next = node->m_next` [cite: 2].
     * If `prev` is `nullptr` (head deletion): invoke `m_buckets[index].DeleteHead()` [cite: 2].
     * Decrement `m_size` and return [cite: 2].

---

### 4.3 Utility Methods

* **`int size() const`**: Returns current element count `m_size` [cite: 2]. Time complexity: $O(1)$.
* **`bool empty() const`**: Returns `true` if `m_size == 0` [cite: 2]. Time complexity: $O(1)$.
* **`void display() const`**: Iterates through all buckets and linked lists to print entries formatted as `{ key1: val1, key2: val2, }` to standard output (`std::cout`) [cite: 2].

---

## 5. Complexity Analysis

| Operation | Average Case | Worst Case (High Collisions) | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Search (`contains` / `at`)** | $O(1)$ | $O(N)$ | $O(1)$ |
| **Insertion (`insert`)** | $O(1)$ amortized | $O(N)$ | $O(1)$ |
| **Deletion (`erase`)** | $O(1)$ | $O(N)$ | $O(1)$ |
| **Rehashing (`rehash`)** | $O(N)$ | $O(N)$ | $O(N)$ |
| **Overall Space Usage** | — | — | $O(N + C)$ ($C = \text{Capacity}$) |

---

## 6. Known Constraints & Design Considerations

1. **Load Factor Maintenance & Importance:** 
   * **Definition:** Calculated as $\alpha = \frac{\text{m\_size}}{\text{m\_capacity}}$, measuring table fullness.
   * **Threshold:** Maintained at $\le 0.75$ [cite: 2].
   * **Performance Impact:** Keeping the load factor low limits collision chain lengths, ensuring operations (`insert`, `contains`, `at`, `erase`) run in $O(1)$ average time rather than degrading toward $O(N)$.
   * **Trade-off:** Serves as a balance between CPU execution speed (reducing collisions) and RAM usage (avoiding excessive empty bucket allocations).
2. **DLL Export Requirements:** The macro `DSALIB_API` allows cross-DLL compilation boundaries on Windows platforms (`__declspec(dllexport)` / `__declspec(dllimport)`) [cite: 2].
3. **Template Implementation Pattern:** Separates headers (`SHashMap.h`) and implementation details (`SHashMap.tpp`) by explicitly including `.tpp` at the bottom of `.h` [cite: 2].
