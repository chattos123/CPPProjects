/**
 * @file SVector.h
 * @brief Declares the SVector class for a dynamic array container holding integer elements in the DSA library.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"

/**
 * @class SVector
 * @brief A dynamically resizable dynamic array container holding integer elements.
 * 
 * Exported via `DSA_API` for dynamic library usage. Manages dynamically allocated buffer space,
 * automatically doubling capacity upon overflow, and supporting copy/move semantics, direct subscript 
 * indexing, boundary queries, and element-wise concatenation.
 */
class DSA_API SVector {
private:
    int* m_data;     ///< Pointer to dynamically allocated heap storage array.
    int m_size;      ///< Number of active elements currently stored in the vector.
    int m_capacity;  ///< Total number of allocated element slots in heap memory.

    /**
     * @brief Reallocates internal buffer storage to a new capacity limit.
     *
     * @param[in] newCapacity Target capacity size for the newly allocated buffer.
     * @return void
     * @remark Copies existing elements over to the new memory buffer and deallocates old memory.
     */
    void resize(int newCapacity);

public:
    // ---------------- Constructors & Destructor ----------------

    /**
     * @brief Default constructor creating an empty SVector instance.
     * 
     * Initializes internal size to 0 and allocates initial default capacity buffer.
     *
     * @param None
     */
    SVector();

    /**
     * @brief Destructor deallocating dynamic heap memory associated with the vector.
     *
     * @param None
     */
    ~SVector();

    /**
     * @brief Copy constructor performing a deep memory copy of another SVector instance.
     *
     * @param[in] other Source SVector instance to duplicate.
     */
    SVector(const SVector& other);

    /**
     * @brief Copy assignment operator replacing vector contents with a deep copy of another SVector instance.
     *
     * @param[in] other Source SVector instance to copy.
     * @return SVector& Reference to this updated SVector instance.
     * @remark Protects against self-assignment.
     */
    SVector& operator=(const SVector& other);

    /**
     * @brief Move constructor transferring resource ownership from an rvalue SVector instance.
     *
     * @param[in,out] other Rvalue reference to source SVector instance.
     */
    SVector(SVector&& other) noexcept;

    /**
     * @brief Move assignment operator transferring resource ownership from an rvalue SVector instance.
     *
     * @param[in,out] other Rvalue reference to source SVector instance.
     * @return SVector& Reference to this updated SVector instance.
     * @remark Protects against self-assignment.
     */
    SVector& operator=(SVector&& other) noexcept;

    // ---------------- Element Access & Modifiers ----------------

    /**
     * @brief Appends a new integer value to the end of the vector.
     *
     * @param[in] value Integer value to push onto the rear.
     * @return void
     * @remark Automatically invokes `resize()` to double capacity when size reaches full capacity.
     */
    void push_back(int value);

    /**
     * @brief Removes the last element from the end of the vector.
     *
     * @param None
     * @return void
     * @remark Decrements `m_size` by 1. No-op if vector is empty.
     */
    void pop_back();

    /**
     * @brief Boundary-checked access to the mutable element reference at the specified index.
     *
     * @param[in] index 0-based element position offset.
     * @return int& Mutable reference to target element.
     * @throws std::out_of_range If `index < 0` or `index >= m_size`.
     */
    int& at(int index);

    /**
     * @brief Boundary-checked access to the constant element reference at the specified index.
     *
     * @param[in] index 0-based element position offset.
     * @return const int& Immutable reference to target element.
     * @throws std::out_of_range If `index < 0` or `index >= m_size`.
     */
    const int& at(int index) const;

    /**
     * @brief Retrieves the current number of active elements in the vector.
     *
     * @param None
     * @return int Active element count.
     * @remark Inline query providing O(1) time complexity.
     */
    inline int size() const { return m_size; }

    /**
     * @brief Retrieves total allocated buffer capacity.
     *
     * @param None
     * @return int Total allocated slot count.
     * @remark Inline query providing O(1) time complexity.
     */
    inline int capacity() const { return m_capacity; }

    /**
     * @brief Checks whether the vector contains no elements.
     *
     * @param None
     * @return true If `m_size == 0`.
     * @return false If vector contains one or more elements.
     * @remark Inline query providing O(1) time complexity.
     */
    inline bool empty() const { return m_size == 0; }

    /**
     * @brief Outputs vector contents to standard output formatted as `[ elem1 elem2 ... ]`.
     *
     * @param None
     * @return void
     * @remark Non-destructive display method.
     */
    void display() const;

    // ---------------- Operator Overloads ----------------

    /**
     * @brief Subscript operator for unchecked mutable access to element at index.
     *
     * @param[in] index 0-based element index position.
     * @return int& Mutable reference to target element.
     */
    int& operator[](int index);

    /**
     * @brief Subscript operator for unchecked constant access to element at index.
     *
     * @param[in] index 0-based element index position.
     * @return const int& Immutable reference to target element.
     */
    const int& operator[](int index) const;

    /**
     * @brief Concatenates contents of another SVector onto this vector, producing a combined vector result.
     *
     * @param[in] other SVector instance to append.
     * @return SVector Newly constructed SVector instance containing elements from both vectors in sequence.
     */
    SVector operator+(const SVector& other) const;
};