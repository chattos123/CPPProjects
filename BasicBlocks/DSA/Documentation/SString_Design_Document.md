# Detailed Design Document: `SString`

---

## 1. Class Overview & Architectural Goals

`SString` is an immutable wide-character string class designed to provide safe string handling for Unicode-aware applications. It stores data internally as `wchar_t` and exposes a modern API for creating, comparing, transforming, and tokenizing text without mutating existing string instances.

### Key architectural goals

- Immutable semantics: all mutating operations return new `SString` objects.
- Safe memory management: owns a heap-allocated wide-character buffer and avoids dangling string views.
- Unicode compatibility: supports conversions between narrow UTF-8 (`char*`) and wide-character (`wchar_t*`) strings.
- Convenience operations: provides case transformation, reversal, substring extraction, tokenization, and safe indexing.
- Cross-platform conversions: uses `MultiByteToWideChar` on Windows and `iconv` on POSIX platforms.

---

## 2. Component Collaboration & Dependencies

```
+----------------+      +-----------------+      +----------------+
|                |      |                 |      |                |
|    SString     | <--> |  wchar_t* Str   | <--> |  memory buffer |
|                |      |                 |      |                |
+----------------+      +-----------------+      +----------------+
        |                        |
        |                        +--> `allocate_and_copy()`
        |                        |
        +--> `safe_copy()`       +--> `safe_concat()`
        |
        +--> `MultiByteToWideChar` / `iconv`

```

### Primary collaborators

- `std::wstring` — used internally during UTF-8 to wide-string conversion.
- `std::vector<SString>` — returned by tokenization methods.
- `std::ostream` / `std::istream` — expected for stream operator support.
- Platform APIs:
  - Windows: `MultiByteToWideChar`
  - POSIX: `iconv`

---

## 3. Class Diagram & Member Specifications

### 3.1 Private Data Members

| Member | Type | Description |
|---|---|---|
| `wchar_t* Str` | pointer | Owned wide-character buffer containing the string contents. Always null-terminated. |
| `int str_len` | int | Stored string length excluding the null terminator. |

### 3.2 Private Helper Methods

#### `void allocate_and_copy(const wchar_t* s)`
- Allocates a new `wchar_t` buffer and copies the input wide string.
- If `s` is `nullptr`, allocates an empty wide string buffer containing `L'\0'`.
- Guarantees `Str` is never left as a null pointer.

#### `static void safe_copy(wchar_t* dest, const wchar_t* src, size_t max_len)`
- Copies up to `max_len - 1` characters and ensures null termination.
- Protects against buffer overflows and invalid source pointers.

#### `static void safe_concat(wchar_t* dest, const wchar_t* src, size_t max_len)`
- Appends `src` to `dest` without exceeding `max_len - 1` characters.
- Preserves safe null-termination semantics.

---

## 4. Public API Design

### 4.1 Constructors

#### `SString()`
- Default constructor.
- Initializes an empty string with a one-character wide buffer containing `L'\0'`.

#### `explicit SString(const wchar_t* s)`
- Constructs from an existing wide-character string.
- Performs a deep copy of the source buffer.

#### `explicit SString(const char* s)`
- Constructs from a narrow UTF-8 or ASCII string.
- Converts to wide characters using platform-specific conversion facilities.
- If conversion fails or input is null, produces an empty string.

#### `SString(const SString& other)`
- Copy constructor.
- Creates a deep copy of `other` to ensure immutable semantics.

---

### 4.2 Assignment Operators

- `SString& operator=(const SString& other)` — deep copy assignment.
- `SString& operator=(const wchar_t* s)` — assign from wide string.
- `SString& operator=(const char* strSource)` — assign from narrow UTF-8/ASCII string.

All assignment overloads replace current storage safely, freeing prior memory before allocating new contents.

---

### 4.3 Accessors & Utilities

#### `const wchar_t& operator[](int index) const`
- Read-only character access.
- Expected to validate `index` and throw `std::out_of_range` if invalid.

#### `wchar_t& operator[](int index)`
- Writable character access.
- Also expected to enforce range checks.

#### `int length() const`
- Returns the number of characters in the string, excluding the null terminator.

#### `const wchar_t* c_str() const`
- Returns the internal wide-character buffer pointer.

#### `const char* c_charString() const`
- Returns a UTF-8 encoded narrow string pointer.
- The returned buffer is internally managed and valid until the next call.

#### `std::wstring ToString() const`
- Converts the internal wide string to an `std::wstring` instance.

#### `void Clear()`
- Resets the string to empty.
- Preserves the immutability contract only if the method returns a new `SString` instance; if it modifies in place, this is a design exception.

---

### 4.4 Transformation Methods

#### `SString to_upper() const`
- Returns a new `SString` with all characters converted to uppercase.

#### `SString to_lower() const`
- Returns a new `SString` with all characters converted to lowercase.

#### `SString change_case() const`
- Returns a new `SString` with toggled case for each character.

#### `SString revert() const`
- Returns a new `SString` containing the characters in reverse order.

#### `SString substring(int start, int length) const`
- Extracts a substring beginning at `start` for `length` characters.
- Expected to throw `std::out_of_range` for invalid range values.

---

### 4.5 Tokenization

`SString` provides overloaded `Tokenize()` methods that split text into a vector of `SString` tokens.

- `std::vector<SString> Tokenize(const wchar_t* delimiters = L" \t\n") const`
- `std::vector<SString> Tokenize(const char* delimiters) const`
- `std::vector<SString> Tokenize(const std::string delimiters) const`
- `std::vector<SString> Tokenize(const SString delimiters) const`

This design supports both wide and narrow delimiter specifications while preserving immutability.

---

### 4.6 Comparison Helpers

#### `bool match_string(const wchar_t* s) const`
- Compares the stored string to another wide-character string.
- Returns `true` when contents are equal.

#### Static helpers
- `static bool IsEmpty(const SString& s)`
- `static bool IsNull(const SString& s)`
- `static bool IsNullOrEmpty(const SString& s)`

These utility functions simplify common string state checks and make client code more expressive.

---

### 4.7 Concatenation Operators

- `SString operator+(const SString& other) const`
- `SString operator+(const wchar_t* s) const`
- `SString operator+(const char* s) const`

Concatenation returns a new `SString` instance without modifying the operands.

---

## 5. Design Rationale

- Immutable strings reduce accidental side effects and simplify reasoning about text transformations.
- Wide-character storage enables native Unicode support on platforms where `wchar_t` represents UTF-16 or UTF-32.
- Explicit conversion from UTF-8 ensures compatibility with narrow-string APIs.
- Internal helper methods keep low-level memory operations safe and reusable.

---

## 6. Extension Points

- Add explicit move semantics via `SString(SString&&)` and `SString& operator=(SString&&)`.
- Add `operator==` and `operator!=` overloads.
- Add `std::ostream& operator<<` and `std::istream& operator>>` for stream-based I/O.
- Add locale-aware casing and Unicode normalization.
- Add a `find()` / `indexOf()` API for substring search.

---

## 7. Notes

- The design assumes `SString` owns its own storage and does not share mutable buffers.
- The class is primarily optimized for safety and correctness rather than maximally compact or high-performance string operations.
- This document focuses on the public API and immutability contract rather than every internal implementation detail.
