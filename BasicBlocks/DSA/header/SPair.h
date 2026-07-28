/**
 * @file SPair.h
 * @brief Declares the templated SPair class and make_spair helper utility, providing std::pair-like functionality.
 * @author Soumyajit C
 * @date 2026
 */

#pragma once

#include "ExportMacro.h"
#include <utility>   // for std::move

/**
 * @class SPair
 * @brief A generic key-value or two-element tuple container holding two arbitrary public values (`first` and `second`).
 * 
 * Provides a lightweight wrapper similar to `std::pair`, supporting value construction, 
 * copy and move semantics, and lexicographical relational comparison operators.
 *
 * @tparam T1 Type of the first stored element.
 * @tparam T2 Type of the second stored element.
 */
template <typename T1, typename T2>
class SPair
{
public:
    T1 first;  ///< The first stored value.
    T2 second; ///< The second stored value.

    /**
     * @brief Default constructor. Value-initializes both `first` and `second`.
     *
     * @param None
     */
    SPair() : first(), second() {}

    /**
     * @brief Parameterized constructor initializing `first` and `second` with supplied values.
     *
     * @param[in] a Constant reference to the value for the first element.
     * @param[in] b Constant reference to the value for the second element.
     */
    SPair(const T1& a, const T2& b) : first(a), second(b) {}

    /**
     * @brief Copy constructor performing element-wise copy initialization.
     *
     * @param[in] other Source `SPair` instance to copy from.
     */
    SPair(const SPair& other) : first(other.first), second(other.second) {}

    /**
     * @brief Move constructor performing element-wise move transfers.
     *
     * @param[in,out] other Rvalue reference to the source `SPair` instance to move from.
     * @remark Marked `noexcept` to allow optimized container reallocations (e.g., inside `std::vector`).
     */
    SPair(SPair&& other) noexcept
        : first(std::move(other.first)), second(std::move(other.second)) {}

    /**
     * @brief Copy assignment operator performing element-wise assignment.
     *
     * @param[in] other Source `SPair` instance to copy.
     * @return SPair& Reference to this updated `SPair` instance.
     * @remark Protects against self-assignment.
     */
    SPair& operator=(const SPair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator performing element-wise resource transfer.
     *
     * @param[in,out] other Rvalue reference to the source `SPair` instance to move.
     * @return SPair& Reference to this updated `SPair` instance.
     * @remark Protects against self-assignment and marked `noexcept`.
     */
    SPair& operator=(SPair&& other) noexcept {
        if (this != &other) {
            first = std::move(other.first);
            second = std::move(other.second);
        }
        return *this;
    }

    /**
     * @brief Equality comparison operator.
     *
     * @param[in] other `SPair` instance to compare against.
     * @return true If both `first` and `second` members are equal.
     * @return false Otherwise.
     */
    bool operator==(const SPair& other) const {
        return first == other.first && second == other.second;
    }

    /**
     * @brief Inequality comparison operator.
     *
     * @param[in] other `SPair` instance to compare against.
     * @return true If either `first` or `second` member differs.
     * @return false Otherwise.
     */
    bool operator!=(const SPair& other) const {
        return !(*this == other);
    }

    /**
     * @brief Lexicographical less-than operator.
     *
     * Compares `first` elements first. If they are equivalent, compares `second` elements.
     *
     * @param[in] other `SPair` instance to compare against.
     * @return true If this instance is lexicographically less than `other`.
     * @return false Otherwise.
     */
    bool operator<(const SPair& other) const {
        return (first < other.first) ||
               (!(other.first < first) && second < other.second);
    }

    /**
     * @brief Lexicographical greater-than operator.
     *
     * @param[in] other `SPair` instance to compare against.
     * @return true If this instance is lexicographically greater than `other`.
     * @return false Otherwise.
     */
    bool operator>(const SPair& other) const {
        return other < *this;
    }

    /**
     * @brief Lexicographical less-than-or-equal operator.
     *
     * @param[in] other `SPair` instance to compare against.
     * @return true If this instance is less than or equal to `other`.
     * @return false Otherwise.
     */
    bool operator<=(const SPair& other) const {
        return !(other < *this);
    }

    /**
     * @brief Lexicographical greater-than-or-equal operator.
     *
     * @param[in] other `SPair` instance to compare against.
     * @return true If this instance is greater than or equal to `other`.
     * @return false Otherwise.
     */
    bool operator>=(const SPair& other) const {
        return !(*this < other);
    }
};

/**
 * @brief Helper factory function to construct an `SPair` instance with deduced template argument types.
 *
 * Mirroring `std::make_pair`, this function allows creating `SPair` objects without explicitly specifying type parameters.
 *
 * @tparam T1 Deducted type of the first element.
 * @tparam T2 Deducted type of the second element.
 * @param[in] a First element value.
 * @param[in] b Second element value.
 * @return SPair<T1, T2> A newly constructed `SPair` instance containing `a` and `b`.
 */
template <typename T1, typename T2>
SPair<T1, T2> make_spair(T1 a, T2 b) {
    return SPair<T1, T2>(a, b);
}