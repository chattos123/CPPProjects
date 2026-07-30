# Detailed Design Document: `SListCircularQT<T>`

---

## 1. Class Overview & Architectural Goals

The `SListCircularQT<T>` class is a **generic, type‑safe circular singly‑linked list** that supports arbitrary element types. It provides efficient insertion at both head and tail, removal from head, and rotation in constant time. Unlike a standard singly‑linked list, the tail node’s `next` pointer references the head node, enabling circular traversal.

### Key Architectural Characteristics
* **List Type:** Circular singly‑linked list.  
* **Underlying Storage:** Dynamically allocated nodes (`Node { T value; Node* next; }`).  
* **Circular Property:** `tail->next` always points to the head node.  
* **State Tracking:** Maintains `m_tail` pointer and `m_count`.  
* **Error Handling:** Throws `std::out_of_range` on invalid operations (e.g., `PopFront` on empty list).  
* **Template Flexibility:** Supports any type `T` with copy/move semantics.  

---

## 2. Component Collaboration & Dependencies

```
+---------------------------------------------------+
|               SListCircularQT<T>                  |
+---------------------------------------------------+
| - m_tail : Node*                                  |
| - m_count: int                                    |
+---------------------------------------------------+
| + PushBack(const T&)                              |
| + PushFront(const T&)                             |
| + PopFront() : T                                  |
| + Rotate()                                        |
| + Contains(const T&) : bool                       |
| + Size() : int                                    |
| + IsEmpty() : bool                                |
| + copy/move ctor & assignment                     |
+---------------------------------------------------+
```

---

## 3. Class Diagram & Member Specifications

### 3.1 Private Data Members

| Member Name | Data Type | Description |
| :---        | :---      | :--- |
| `m_tail`    | `Node*`   | Tail pointer; when non‑null, `m_tail->next` is the head. |
| `m_count`   | `int`     | Number of active nodes in the list. |

---

### 3.2 Special Member Functions

* **Default Constructor:** Initializes `m_tail = nullptr`, `m_count = 0`.  
* **Destructor:** Frees all nodes.  
* **Copy Constructor:** Deep copies all nodes preserving order.  
* **Copy Assignment Operator:** Clears current list, then deep copies from source.  
* **Move Constructor:** Transfers ownership of nodes and resets source.  
* **Move Assignment Operator:** Clears current list, transfers ownership, resets source.  

---

## 4. Public API Design & Operation Logic

### 4.1 Core Operations

#### `bool PushBack(const T& value)`
* Appends a new node at the tail.  
* If empty, node points to itself (`next = node`).  
* Otherwise, node->next = head, tail->next = node, tail = node.  
* Increments `m_count`.  
* Returns `false` if allocation fails.

#### `bool PushFront(const T& value)`
* Inserts a new node at the head.  
* If empty, node points to itself, tail = node.  
* Otherwise, node->next = head, tail->next = node.  
* Increments `m_count`.  
* Returns `false` if allocation fails.

---
## Sequence Diagram: `PushBack()`

### Context
- `m_tail` points to the tail node.
- `head` is `m_tail->next`.

### Operation
- Create a new node.
- If empty: node->next = node, `m_tail = node`.
- Otherwise: node->next = head, `m_tail->next = node`, `m_tail = node`.

---

```
Before PushBack():
    m_tail -> Tail
    head   -> Head (m_tail->next)

PushBack(newNode):
    newNode->next = Head
    m_tail->next = newNode
    m_tail = newNode

After PushBack():
    m_tail -> newNode
    head   -> Head (m_tail->next)
```

**Result:**  
- New node becomes the tail.  
- Head remains unchanged.  
- Circular property preserved (`m_tail->next` still points to head).  

---

### 🔑 Key Insights
- **PushFront:** Efficient O(1) insertion at head; tail pointer unchanged.  
- **PushBack:** Efficient O(1) insertion at tail; tail pointer updated to new node.  
- **Circular invariant:** Always maintained — `m_tail->next` points to head.  
- **Edge case:** If list is empty, both operations initialize a single node pointing to itself.  

---

## Sequence Diagram: `PushFront()`

### Context
- `m_tail` points to the tail node.
- `head` is `m_tail->next`.

### Operation
- Create a new node.
- If empty: node->next = node, `m_tail = node`.
- Otherwise: node->next = head, `m_tail->next = node`.

---

```
Before PushFront():
    m_tail -> Tail
    head   -> Head (m_tail->next)

PushFront(newNode):
    newNode->next = Head
    m_tail->next = newNode

After PushFront():
    m_tail -> Tail
    head   -> newNode (m_tail->next)
```

**Result:**  
- New node becomes the head.  
- Tail remains unchanged.  
- Circular property preserved (`m_tail->next` points to new head).  

---

#### `T PopFront()`
* Removes and returns the head node (`m_tail->next`).  
* If only one node, resets `m_tail = nullptr`.  
* Otherwise, tail->next = head->next.  
* Decrements `m_count`.  
* Throws `std::out_of_range("List is empty")` if empty.
---

## Sequence Diagram: `PopFront()` in `SListCircularQT<T>`

### Context
- `m_tail` points to the tail node.
- `head` is `m_tail->next`.

### Operation
- Remove the head node.
- If head == tail (only one node), delete it and set `m_tail = nullptr`.
- Otherwise, set `m_tail->next = head->next` and delete head.

---

### UML‑style Sequence Diagram

```
+-------------------+        +-------------------+        +-------------------+
|       Tail        |        |       Head        |        |   Next (new head) |
+-------------------+        +-------------------+        +-------------------+
| value: T_tail     |        | value: T_head     |        | value: T_next     |
| next ------------>|------->| next ------------>|------->| next ------------>...
+-------------------+        +-------------------+        +-------------------+

Before PopFront():
    m_tail -> Tail
    head   -> Head (m_tail->next)

PopFront():
    if (Head == Tail):
        delete Head
        m_tail = nullptr
    else:
        m_tail->next = Head->next
        delete Head

After PopFront():
    m_tail -> Tail
    head   -> Next (m_tail->next)
```

---

### Step‑by‑Step Transition

1. **Initial State**  
   - `m_tail` points to Tail.  
   - `head = m_tail->next` points to Head.  

2. **PopFront() Execution**  
   - If only one node: delete Head, set `m_tail = nullptr`.  
   - Otherwise: update `m_tail->next = head->next`, delete Head.  

3. **Resulting State**  
   - `m_tail` still points to Tail.  
   - `head = m_tail->next` points to Next.  
   - The old head is removed, and the new head is Next.  

---

### Key Insight
- **Constant‑time removal:** No traversal required.  
- **Circular property preserved:** After removal, `m_tail->next` still points to the new head.  
- **Edge case:** When the list has only one node, both head and tail are deleted, leaving the list empty.  

---
---

#### `void Rotate()`
* Advances `m_tail = m_tail->next`.  
* Effectively moves head to tail.  
* No‑op if empty.

---

---
## Sequence Diagram: `Rotate()` in `SListCircularQT<T>`

### Context
- `m_tail` points to the tail node.
- `head` is `m_tail->next`.

### Operation
- `Rotate()` simply advances `m_tail = m_tail->next`.
- This makes the old head become the new tail, and the new head is the next node.

---

### UML‑style Sequence Diagram

```
+-------------------+        +-------------------+        +-------------------+
|       Tail        |        |       Head        |        |   Next (new head) |
+-------------------+        +-------------------+        +-------------------+
| value: T_tail     |        | value: T_head     |        | value: T_next     |
| next ------------>|------->| next ------------>|------->| next ------------>...
+-------------------+        +-------------------+        +-------------------+

Before Rotate():
    m_tail -> Tail
    head   -> Head (m_tail->next)

After Rotate():
    m_tail -> Head
    head   -> Next (m_tail->next)
```

---

### Step‑by‑Step Transition

1. **Initial State**  
   - `m_tail` points to Tail.  
   - `head = m_tail->next` points to Head.  

2. **Rotate() Execution**  
   - `m_tail = m_tail->next`.  

3. **Resulting State**  
   - `m_tail` now points to Head.  
   - `head = m_tail->next` points to Next.  
   - The old head becomes the new tail.  

---

### Key Insight
- **Constant‑time operation:** No traversal required.  
- **Circular property preserved:** `m_tail->next` always points to the logical head.  
- **Use case:** Efficient round‑robin scheduling or rotation of active elements.  

---
---

### 4.2 Utility Methods

* **`bool Contains(const T& val) const`** → Traverses circular list for `m_count` steps, returns true if found.  
* **`int Size() const`** → Returns `m_count`.  
* **`bool IsEmpty() const`** → Returns `m_tail == nullptr`.  
* **`void ClearAll()`** → Frees all nodes, resets `m_tail = nullptr`, `m_count = 0`.  

---

## 5. Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **PushBack** | $O(1)$ | $O(1)$ |
| **PushFront** | $O(1)$ | $O(1)$ |
| **PopFront** | $O(1)$ | $O(1)$ |
| **Rotate**   | $O(1)$ | $O(1)$ |
| **Contains** | $O(N)$ | $O(1)$ |
| **Copy**     | $O(N)$ | $O(N)$ |
| **Move**     | $O(1)$ | $O(1)$ |

---

## 6. Known Constraints & Design Considerations

1. **Dynamic Allocation:** Each node allocated individually; allocation failure returns `false`.  
2. **Circular Traversal:** Iterators must track `m_count` to avoid infinite loops.  
3. **Error Handling:** `PopFront` throws on empty list.  
4. **Move Semantics:** Efficient transfer of ownership by stealing `m_tail` and `m_count`.  
5. **DLL Export:** `DSA_API` macro ensures cross‑DLL compatibility.  

---