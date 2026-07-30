# Detailed Design Document: `SCircularQT<T>`

---

## 1. Class Overview & Architectural Goals

The `SCircularQT<T>` class is a **generic, type‑safe circular FIFO queue** that supports arbitrary element types. It provides efficient enqueue, dequeue, and front element access in constant time using modular arithmetic for wrap‑around indexing.

### Key Architectural Characteristics
* **Queue Type:** Circular queue with fixed maximum capacity (`QUEUE_MAX`).
* **Underlying Storage:** Static array of type `T` (`T data[QUEUE_MAX]`).
* **Indexing Strategy:** Modular arithmetic for wrap‑around behavior.
* **State Tracking:** Maintains `frontIndex`, `rearIndex`, and `count`.
* **Error Handling:** Throws `std::runtime_error` on overflow/underflow.
* **Template Flexibility:** Supports any type `T` with copy/move semantics.

---

## 2. Component Collaboration & Dependencies

```
+---------------------------------------------------+
|                 SCircularQT<T>                    |
+---------------------------------------------------+
| - data[QUEUE_MAX] : T                             |
| - frontIndex      : int                           |
| - rearIndex       : int                           |
| - count           : int                           |
+---------------------------------------------------+
| + enqueue(const T&)                               |
| + dequeue() : T                                   |
| + front() : T                                     |
| + isEmpty() : bool                                |
| + isFull() : bool                                 |
| + copy/move ctor & assignment                     |
+---------------------------------------------------+
```

---

## 3. Class Diagram & Member Specifications

### 3.1 Private Data Members

| Member Name   | Data Type | Description |
| :---          | :---      | :--- |
| `data`        | `T[QUEUE_MAX]` | Static array buffer holding queue elements of type `T`. |
| `frontIndex`  | `int` | Index of the current front element. |
| `rearIndex`   | `int` | Index of the current rear element. |
| `count`       | `int` | Number of active elements in the queue. |

---

### 3.2 Special Member Functions

* **Default Constructor:** Initializes indices and count to empty state.  
* **Destructor:** Defaulted.  
* **Copy Constructor:** Deep copies all elements and indices.  
* **Copy Assignment Operator:** Replaces contents with another queue’s state.  
* **Move Constructor:** Transfers ownership of buffer contents and indices, resets source.  
* **Move Assignment Operator:** Transfers state into existing queue, resets source.

---

## 4. Public API Design & Operation Logic

### 4.1 Core Operations

#### `void enqueue(const T& value)`
* Inserts a new element at the rear.  
* Updates `rearIndex = (rearIndex + 1) % QUEUE_MAX`.  
* Stores `value` in `data[rearIndex]`.  
* Increments `count`.  
* Throws `std::runtime_error("Circular queue overflow")` if full.

#### `T dequeue()`
* Removes and returns the front element.  
* Retrieves `data[frontIndex]`.  
* Updates `frontIndex = (frontIndex + 1) % QUEUE_MAX`.  
* Decrements `count`.  
* Throws `std::runtime_error("Circular queue underflow")` if empty.

#### `T front() const`
* Returns the front element without removing it.  
* Throws `std::runtime_error("Circular queue is empty")` if empty.

---

### 4.2 Utility Methods

* **`bool isEmpty() const`** → `count == 0`.  
* **`bool isFull() const`** → `count == QUEUE_MAX`.

---

## 5. Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Enqueue** | $O(1)$ | $O(1)$ |
| **Dequeue** | $O(1)$ | $O(1)$ |
| **Front**   | $O(1)$ | $O(1)$ |
| **isEmpty** | $O(1)$ | $O(1)$ |
| **isFull**  | $O(1)$ | $O(1)$ |
| **Copy/Move** | $O(N)$ for copy, $O(N)$ moves or $O(1)$ pointer transfer if dynamic | $O(N)$ |

---

## 6. Known Constraints & Design Considerations

1. **Fixed Capacity:** Limited by `QUEUE_MAX`.  
2. **Error Handling:** Overflow/underflow exceptions.  
3. **Template Flexibility:** Works with any type `T` that supports copy/move.  
4. **Move Semantics:** Efficient transfer of heavy objects.  
5. **DLL Export:** `DSA_API` macro ensures cross‑DLL compatibility.  

---