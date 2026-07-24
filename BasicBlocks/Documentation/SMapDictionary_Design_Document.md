# Detailed Design Document: `SMapDictionary<K, V>`

---

## 1. Class Overview & Architectural Goals

The `SMapDictionary<K, V>` class is a generic, type-safe associative container (dictionary/hash map) that provides key-value pair storage, fast lookups, insertion, and deletion using $O(1)$ average time complexity.

### Key Architectural Characteristics
* **Collision Resolution:** **Separate Chaining** using C++ standard library doubly-linked lists (`std::list`).
* **Underlying Storage:** Dynamic bucket array managed via standard vector (`std::vector`).
* **Data Representation:** Elements are stored as custom key-value pairs (`SPair<K, V>`).
* **Hashing Strategy:** Utilizes standard hashing functor `std::hash<K>`.
* **Dynamic Resizing:** Dynamic rehashing (array doubling) triggered automatically when the load factor exceeds $0.75$.

---

## 2. Component Collaboration & Dependencies

```
+-----------------------------------------------------------------------+
|                         SMapDictionary<K, V>                          |
+-----------------------------------------------------------------------+
                                   |
            +----------------------+----------------------+
            | 1:N                                         | 1:1
            v                                             v
+-----------------------+                         +---------------------+
| std::vector<std::list>|                         |     std::hash<K>    |
+-----------------------+                         +---------------------+
            |
            | Contains Bucket Lists
            v
+-----------------------+
|   std::list<SPair>    |
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
| `m_buckets` | `std::vector<std::list<SPair<K,V>>>` | Dynamic array of bucket lists representing collision chains. |
| `m_size` | `int` | Total count of key-value pairs stored in the dictionary. |
| `m_capacity` | `int` | Total number of bucket slots allocated in `m_buckets`. |

---

### 3.2 Private Helper Methods

#### `int getBucketIndex(const K& key) const`
* **Purpose:** Computes the array index in `m_buckets` corresponding to a given key.
* **Logic:** Computes `std::hash<K>{}(key) % m_capacity`.
* **Time Complexity:** $O(1)$ (assuming constant time for `std::hash<K>`).

#### `void rehash()`
* **Purpose:** Expands internal capacity to maintain average $O(1)$ operational performance.
* **Algorithmic Steps:**
  1. Compute `newCapacity = m_capacity * 2`.
  2. Create temporary vector `newBuckets` of size `newCapacity`.
  3. Iterate across all current buckets and node pairs (`SPair<K,V>`).
  4. Recalculate target index for each key in the new table:
     $$\text{newIndex} = \text{std::hash<K>}\{\}(\text{kv.first}) \pmod{\text{newCapacity}}$$
  5. Append entry to `newBuckets[newIndex]`.
  6. Swap `m_buckets` with `newBuckets` and set `m_capacity = newCapacity`.

---

## 4. Public API Design & Operation Logic

### 4.1 Constructors

```cpp
SMapDictionary(int capacity = 8);
```
* **Description:** Constructs an empty dictionary instance.
* **Pre-conditions:** `capacity > 0`.
* **Post-conditions:** `m_size == 0`, `m_capacity` set to argument value (default 8), `m_buckets` initialized with `capacity` empty lists.

---

### 4.2 Core Operations

#### `void insert(const K& key, const V& value)`
* **Description:** Inserts a new key-value pair or updates the existing value if the key already exists.
* **Control Flow:**
  1. Calculate `index = getBucketIndex(key)`.
  2. Search `m_buckets[index]` sequentially for `key`.
  3. **If match found:** Update `kv.second = value` and exit.
  4. **If not found:** Append `SPair<K,V>(key, value)` to `m_buckets[index]` and increment `m_size`.
  5. Check load factor condition:
     $$\text{if } (\text{m\_size} > \text{m\_capacity} \times 0.75) \implies \text{rehash}()$$

#### `bool contains(const K& key) const`
* **Description:** Checks whether a specific key exists in the dictionary.
* **Control Flow:**
  1. Calculate `index = getBucketIndex(key)`.
  2. Search `m_buckets[index]` sequentially.
  3. Return `true` if key is found; otherwise, return `false`.

#### `V& at(const K& key)`
* **Description:** Retrieves a reference to the value associated with `key`.
* **Control Flow:**
  1. Compute `index = getBucketIndex(key)`.
  2. Iterate through `m_buckets[index]`.
  3. If found, return `kv.second`.
  4. Throw `std::out_of_range("Key not found")` if traversal completes without finding `key`.

#### `void erase(const K& key)`
* **Description:** Removes the key-value pair corresponding to `key`.
* **Control Flow:**
  1. Compute `index = getBucketIndex(key)`.
  2. Search `m_buckets[index]` using an iterator.
  3. On match, invoke `m_buckets[index].erase(it)`, decrement `m_size`, and return.

---

### 4.3 Utility Methods

* **`void display() const`**: Traverses all bucket slots and list elements to output contents in `{ key1: value1, key2: value2, }` format to `std::cout`.

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
   * **Definition:** Calculated as $\alpha = \frac{\text{m\_size}}{\text{m\_capacity}}$, measuring overall table fullness.
   * **Threshold:** Maintained at $\le 0.75$.
   * **Performance Impact:** Keeping the load factor low limits collision chain lengths, ensuring operations (`insert`, `contains`, `at`, `erase`) run in $O(1)$ average time rather than degrading toward $O(N)$.
   * **Trade-off:** Serves as a balance between CPU execution speed (reducing collisions) and RAM usage (avoiding excessive empty bucket allocations).
2. **DLL Export Requirements:** The macro `DSALIB_API` allows cross-DLL compilation boundaries on Windows platforms (`__declspec(dllexport)` / `__declspec(dllimport)`).
3. **Template Implementation Pattern:** Separates headers (`SMapDictionary.h`) and implementation details (`SMapDictionary.tpp`) by explicitly including `.tpp` at the bottom of `.h`.
