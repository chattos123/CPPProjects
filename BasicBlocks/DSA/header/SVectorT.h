/**
 * @file SVectorT.h
 * @brief Declares the templated SVectorT class for a type-safe dynamic array container.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

#include <iostream>
#include <stdexcept>

/**
 * @class SVectorT
 * @brief A generic resizable array container supporting deep copy, move semantics, STL iteration, and boundary operations.
 *
 * @tparam T Type of elements stored within the dynamic array.
 */
template <typename T>
class SVectorT 
{
private:
    T* m_data;       ///< Pointer to dynamically allocated dynamic array storage.
    int m_size;      ///< Number of active elements currently stored in the vector.
    int m_capacity;  ///< Total allocated slot capacity in dynamic memory.

    /**
     * @brief Internal helper to reallocate dynamic memory buffer to a new capacity.
     *
     * @param[in] newCapacity Target buffer capacity size.
     * @return void
     * @remark Copies/moves existing elements to newly allocated storage and releases old buffer.
     */
    void resize(int newCapacity);

public:
    // ---------------- STL Iterator Type Aliases ----------------
    using iterator = T*;                  ///< Type alias for mutable random-access iterator.
    using const_iterator = const T*;        ///< Type alias for constant read-only random-access iterator.

    /**
     * @brief Returns a mutable iterator to the first element in the vector.
     *
     * @param None
     * @return iterator Pointer to the first element buffer position.
     */
    iterator begin() { return m_data; }

    /**
     * @brief Returns a mutable iterator pointing past the last element in the vector.
     *
     * @param None
     * @return iterator Pointer referencing position immediately past the final active element.
     */
    iterator end() { return m_data + m_size; }

    /**
     * @brief Returns a constant iterator to the first element in the vector.
     *
     * @param None
     * @return const_iterator Constant pointer to the first element buffer position.
     */
    const_iterator begin() const { return m_data; }

    /**
     * @brief Returns a constant iterator pointing past the last element in the vector.
     *
     * @param None
     * @return const_iterator Constant pointer referencing position immediately past the final active element.
     */
    const_iterator end() const { return m_data + m_size; }

    /**
     * @brief Explicit constant iterator method to access the first element in the vector.
     *
     * @param None
     * @return const_iterator Constant pointer to the first element buffer position.
     */
    const_iterator cbegin() const { return m_data; }

    /**
     * @brief Explicit constant iterator method pointing past the last element in the vector.
     *
     * @param None
     * @return const_iterator Constant pointer referencing position immediately past the final active element.
     */
    const_iterator cend() const { return m_data + m_size; }

    // ---------------- Constructors & Destructor ----------------

    /**
     * @brief Default constructor creating an empty vector instance.
     *
     * Initializes internal size to 0 and allocates initial default capacity buffer.
     *
     * @param None
     */
    SVectorT();

    /**
     * @brief Destructor deallocating dynamic heap storage allocated for the vector.
     *
     * @param None
     */
    ~SVectorT();

    /**
     * @brief Copy constructor performing a deep copy of another SVectorT instance.
     *
     * @param[in] other Source SVectorT instance to duplicate.
     */
    SVectorT(const SVectorT& other);

    /**
     * @brief Move constructor transferring buffer ownership from an rvalue SVectorT instance.
     *
     * @param[in,out] other Rvalue reference to source SVectorT instance.
     * @remark Marked `noexcept` for performance during container reallocations.
     */
    SVectorT(SVectorT&& other) noexcept;

    /**
     * @brief Copy assignment operator performing a deep copy of another SVectorT instance.
     *
     * @param[in] other Source SVectorT instance to copy.
     * @return SVectorT& Reference to this updated SVectorT instance.
     * @remark Protects against self-assignment.
     */
    SVectorT& operator=(const SVectorT& other);

    /**
     * @brief Move assignment operator transferring buffer ownership from an rvalue SVectorT instance.
     *
     * @param[in,out] other Rvalue reference to source SVectorT instance.
     * @return SVectorT& Reference to this updated SVectorT instance.
     * @remark Protects against self-assignment and marked `noexcept`.
     */
    SVectorT& operator=(SVectorT&& other) noexcept;

    /**
     * @brief Concatenates contents of two SVectorT containers, producing a combined vector result.
     *
     * @param[in] other SVectorT instance to append.
     * @return SVectorT Newly constructed SVectorT instance holding combined elements in sequence.
     */
    SVectorT operator+(const SVectorT& other) const;

    // ---------------- Element Access & Modifiers ----------------

    /**
     * @brief Appends an element to the end of the vector.
     *
     * @param[in] value Constant reference to the element value to insert.
     * @return void
     * @remark Automatically doubles internal capacity when size reaches capacity threshold.
     */
    void push_back(const T& value);

    /**
     * @brief Removes the last element from the end of the vector.
     *
     * @param None
     * @return void
     * @remark Decrements `m_size` by 1. No-op if vector is empty.
     */
    void pop_back();

    /**
     * @brief Accesses element value at the specified index with boundary validation.
     *
     * @param[in] index Zero-based index position of element to access.
     * @return T Copy of element value at target position.
     * @throws std::out_of_range If `index < 0` or `index >= m_size`.
     */
    T at(int index) const;

    /**
     * @brief Subscript operator for unchecked mutable access to element at specified index.
     *
     * @param[in] index Zero-based element index position.
     * @return T& Mutable reference to target element.
     */
    T& operator[](int index);

    /**
     * @brief Subscript operator for unchecked constant access to element at specified index.
     *
     * @param[in] index Zero-based element index position.
     * @return const T& Immutable reference to target element.
     */
    const T& operator[](int index) const;

    /**
     * @brief Retrieves the current number of active elements in the vector.
     *
     * @param None
     * @return int Active element count.
     * @remark Inline query providing O(1) time complexity.
     */
    int size() const { return m_size; }

    /**
     * @brief Retrieves total allocated buffer capacity.
     *
     * @param None
     * @return int Total allocated slot count.
     * @remark Inline query providing O(1) time complexity.
     */
    int capacity() const { return m_capacity; }

    /**
     * @brief Checks whether the vector contains no elements.
     *
     * @param None
     * @return true If `m_size == 0`.
     * @return false If vector contains one or more elements.
     * @remark Inline query providing O(1) time complexity.
     */
    bool empty() const { return m_size == 0; }

    /**
     * @brief Reserves buffer storage capacity for at least `newCapacity` elements.
     *
     * @param[in] newCapacity Target minimum capacity threshold.
     * @return void
     * @remark No-op if `newCapacity <= m_capacity`.
     */
    void reserve(int newCapacity);

    /**
     * @brief Resizes the logical element count of the vector.
     *
     * @param[in] newSize Target new element count.
     * @return void
     * @remark Reallocates buffer if `newSize` exceeds current capacity; default-initializes newly added slots.
     */
    void resizeSize(int newSize);

    /**
     * @brief Outputs vector contents to standard output.
     *
     * @param None
     * @return void
     * @remark Non-destructive display function. Requires `operator<<` to be defined for type T.
     */
    void display() const;
};

// Include template implementation definitions
#include "SVectorT.tpp"