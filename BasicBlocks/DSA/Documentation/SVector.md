# Class Documentation: `SVector`

**File:** `SVector.cpp`

**Author:** Soumyajit C

**Date:** 2026

**Description:** Implements a dynamically resizing `int` array class (`SVector`).

---

## Overview

`SVector` is a specialized sequential dynamic array structure designed specifically for primitive `int` data types. It features exponential reallocation growth (`VECTOR_ATOMICITY = 2`), complete copy and move semantics, element access with bounds verification, and sequence concatenation.

---

## Public Member Functions

### Constructors & Destructor

#### `SVector()`

```cpp
SVector();

```

* **Description:** Default constructor. Constructs an empty vector (`m_data = nullptr`, `m_size = 0`, `m_capacity = 0`).

---

#### `SVector(const SVector& other)`

```cpp
SVector(const SVector& other);

```

* **Description:** Copy constructor. Performs a deep copy of another `SVector`.
* **Parameters:**
* `other` `[in]` – Source `SVector` instance.



---

#### `SVector(SVector&& other) noexcept`

```cpp
SVector(SVector&& other) noexcept;

```

* **Description:** Move constructor. Steals internal array memory from a temporary `SVector`.
* **Parameters:**
* `other` `[in, out]` – Rvalue reference to source object. Leaves source in an empty state.



---

#### `~SVector()`

```cpp
~SVector();

```

* **Description:** Destructor. Deallocates heap memory via `delete[] m_data`.

---

### Assignment Operators

#### `operator=` (Copy & Move)

```cpp
SVector& operator=(const SVector& other);
SVector& operator=(SVector&& other) noexcept;

```

* **Description:** Overloaded copy and move assignment operators.
* **Parameters:**
* `other` – Source vector object.


* **Returns:** `SVector&` – Reference to `*this`.

---

### Capacity & Modifiers

#### `push_back()`

```cpp
void push_back(int value);

```

* **Description:** Appends an integer value to the end of the array. Triggers `resize()` if `m_size == m_capacity`.
* **Parameters:**
* `value` `[in]` – Integer value to append.



---

#### `pop_back()`

```cpp
void pop_back();

```

* **Description:** Removes the last element from the array.
* **Throws:** `std::out_of_range` – If invoked on an empty vector.

---

#### `resize()`

```cpp
void resize(int newCapacity);

```

* **Description:** Reallocates internal storage buffer to `newCapacity` elements.
* **Parameters:**
* `newCapacity` `[in]` – New total element capacity.



---

### Element Access

#### `at()` / `operator[]`

```cpp
int& at(int index);
const int& at(int index) const;

int& operator[](int index);
const int& operator[](int index) const;

```

* **Description:** Provides mutable or read-only element access at the target index.
* **Parameters:**
* `index` `[in]` – Zero-based element index.


* **Throws:** `std::out_of_range` – If `index < 0` or `index >= m_size`.

---

### Operators & Output

#### `operator+`

```cpp
SVector operator+(const SVector& other) const;

```

* **Description:** Concatenates two vectors into a new `SVector` instance.
* **Parameters:**
* `other` `[in]` – Right-hand side `SVector` operand.


* **Returns:** `SVector` – Concatenated vector object.

---

#### `display()`

```cpp
void display() const;

```

* **Description:** Formats and prints elements to standard output (`std::cout`).