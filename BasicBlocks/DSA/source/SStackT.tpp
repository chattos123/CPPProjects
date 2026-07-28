/**
 * @file SStackT.tpp
 * @brief Implementation details for copy construction and assignment operators of the templated SStackT class.
 * @author Soumyajit C
 * @date 2026
 */

#include "SStackT.h"

/**
 * @brief Copy constructor performing an element-wise copy of another SStackT instance.
 *
 * Copies the `topIndex` and all valid element data up to `topIndex` into the new stack buffer.
 *
 * @tparam T Type of elements stored in the stack.
 * @param[in] other Constant reference to the source `SStackT` instance to copy from.
 */
template <typename T>
SStackT<T>::SStackT(const SStackT& other) 
{
    topIndex = other.topIndex;

    for (int i = 0; i <= topIndex; ++i) 
    {
        data[i] = other.data[i];
    }
}

/**
 * @brief Copy assignment operator performing an element-wise copy of another SStackT instance.
 *
 * Replaces current stack contents with data from the source stack after validating against self-assignment.
 *
 * @tparam T Type of elements stored in the stack.
 * @param[in] other Constant reference to the source `SStackT` instance to copy.
 * @return SStackT<T>& Reference to this updated `SStackT` instance.
 * @remark Includes explicit self-assignment check (`this == &other`).
 */
template <typename T>
SStackT<T>& SStackT<T>::operator=(const SStackT& other) 
{
    if (this == &other) return *this; // self-assignment check

    topIndex = other.topIndex;

    for (int i = 0; i <= topIndex; ++i) 
    {
        data[i] = other.data[i];
    }

    return *this;
}