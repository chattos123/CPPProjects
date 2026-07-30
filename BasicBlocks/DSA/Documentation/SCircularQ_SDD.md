# Detailed Design Document: `SCircularQ`

---

## 1. Class Overview & Architectural Goals

The `SCircularQ` class is a fixed-capacity, type-safe **circular FIFO (First-In-First-Out) queue** designed for efficient queue operations using modular arithmetic. It provides constant-time enqueue, dequeue, and front element access while reusing buffer space through wrap-around indexing.

### Key Architectural Characteristics
* **Queue Type:** Circular queue with fixed maximum capacity (`QUEUE_MAX`).
* **Underlying Storage:** Static integer array (`int data[QUEUE_MAX]`).
* **Indexing Strategy:** Modular arithmetic for wrap-around behavior.
* **State Tracking:** Maintains `frontIndex`, `rearIndex`, and `count` for efficient O(1) operations.
* **Error Handling:** Throws `std::runtime_error` on overflow/underflow conditions.

---

## 2. Component Collaboration & Dependencies

```
+---------------------------------------------------+
|                   SCircularQ                      |
+---------------------------------------------------+
| - data[QUEUE_MAX] : int                           |
| - frontIndex      : int                           |
| - rearIndex       : int                           |
| - count           : int                           |
+---------------------------------------------------+
| + enqueue(int)                                    |
| + dequeue() : int                                 |
| + front() : int                                   |
| + isEmpty() : bool                                |
| + isFull() : bool                                 |
+---------------------------------------------------+
```

---

## 3. Class Diagram & Member Specifications

### 3.1 Private Data Members

| Member Name   | Data Type | Description |
| :---          | :---      | :--- |
| `data`        | `int[QUEUE_MAX]` | Static array buffer holding queue elements. |
| `frontIndex`  | `int` | Index of the current front element. |
| `rearIndex`   | `int` | Index of the current rear element. |
| `count`       | `int` | Number of active elements in the queue. |

---

### 3.2 Private Helper Logic

#### Wrap-around Indexing
* **Purpose:** Ensures indices cycle within `[0, QUEUE_MAX-1]`.
* **Logic:** `(index + 1) % QUEUE_MAX`.
* **Time Complexity:** $O(1)$.

---

## 4. Public API Design & Operation Logic

### 4.1 Constructors

```cpp
SCircularQ();
```
* **Description:** Constructs an empty circular queue.
* **Post-conditions:** `frontIndex = 0`, `rearIndex = -1`, `count = 0`.

---

### 4.2 Core Operations

#### `void enqueue(int value)`
* **Description:** Inserts a new integer at the rear of the queue.
* **Control Flow:**
  1. Check `isFull()`. If true, throw `std::runtime_error("Circular queue overflow")`.
  2. Update `rearIndex = (rearIndex + 1) % QUEUE_MAX`.
  3. Store `value` in `data[rearIndex]`.
  4. Increment `count`.

#### `int dequeue()`
* **Description:** Removes and returns the front element.
* **Control Flow:**
  1. Check `isEmpty()`. If true, throw `std::runtime_error("Circular queue underflow")`.
  2. Retrieve `value = data[frontIndex]`.
  3. Update `frontIndex = (frontIndex + 1) % QUEUE_MAX`.
  4. Decrement `count`.
  5. Return `value`.

#### `int front() const`
* **Description:** Returns the front element without removing it.
* **Control Flow:**
  1. Check `isEmpty()`. If true, throw `std::runtime_error("Circular queue is empty")`.
  2. Return `data[frontIndex]`.

---

### 4.3 Utility Methods

* **`bool isEmpty() const`**: Returns `true` if `count == 0`.  
* **`bool isFull() const`**: Returns `true` if `count == QUEUE_MAX`.

---

## 5. Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Enqueue** | $O(1)$ | $O(1)$ |
| **Dequeue** | $O(1)$ | $O(1)$ |
| **Front**   | $O(1)$ | $O(1)$ |
| **isEmpty** | $O(1)$ | $O(1)$ |
| **isFull**  | $O(1)$ | $O(1)$ |

---

## 6. Known Constraints & Design Considerations

1. **Fixed Capacity:**  
   * Maximum size limited by `QUEUE_MAX`.  
   * No dynamic resizing — overflow must be handled explicitly.

2. **Error Handling:**  
   * Overflow → `std::runtime_error("Circular queue overflow")`.  
   * Underflow → `std::runtime_error("Circular queue underflow")`.

3. **DLL Export Requirements:**  
   * `DSA_API` macro ensures compatibility across DLL boundaries.

4. **Template Extension:**  
   * A generic version (`SCircularQT<T>`) can be implemented to support arbitrary types.  
   * Move semantics (`&&`) allow efficient transfer of heavy objects.

---