/**
 * @file STuple.h
 * @brief Declares the generic STuple variadic template class for type-safe heterogeneous tuple storage.
 * @author Soumyajit C
 * @date 2026
 * 
 * @remark Uses recursive template inheritance/composition to store a fixed-size collection of heterogeneous 
 *         values without relying on dynamic allocations or virtual inheritance tables.
 */

#pragma once

#include "ExportMacro.h"
#include <utility>   // for std::forward
#include <cstddef>   // for size_t

/**
 * @class STuple
 * @brief Forward declaration of the generic variadic STuple class template.
 *
 * @tparam Ts Variadic pack representing the element types stored within the tuple.
 */
template <typename... Ts>
class STuple;

/**
 * @class STuple<>
 * @brief Template specialization representing the base case termination for an empty STuple.
 * 
 * Serves as the base termination class for variadic template expansion of `STuple<Head, Tail...>`.
 */
template <>
class STuple<> 
{
public:
    /**
     * @brief Default constructor for empty STuple base case.
     *
     * @param None
     */
    STuple() = default;
};

/**
 * @class STuple<Head, Tail...>
 * @brief Recursive variadic template implementation for a heterogeneous tuple container holding two or more types.
 * 
 * Encapsulates the current element (`head`) and recursively nests remaining elements (`tail`) using 
 * variadic template expansion to achieve static compile-time heterogeneous storage.
 *
 * @tparam Head Type of the first stored element in this tuple level.
 * @tparam Tail Variadic types of remaining trailing elements in the tuple.
 */
template <typename Head, typename... Tail>
class STuple<Head, Tail...> 
{
public:
    Head head;               ///< Stored element value at the current tuple nesting level.
    STuple<Tail...> tail;    ///< Nested sub-tuple holding remaining trailing elements.

    /**
     * @brief Default constructor initializing all tuple elements using default construction.
     *
     * @param None
     */
    STuple() = default;

    /**
     * @brief Parameterized constructor initializing tuple elements via lvalue reference copying.
     *
     * @param[in] h Constant reference to the head element value.
     * @param[in] t Constant references to remaining tail element values.
     */
    STuple(const Head& h, const Tail&... t)
        : head(h), tail(t...) {}

    /**
     * @brief Universal/Forwarding variadic constructor supporting perfect forwarding move and copy semantics.
     *
     * Allows move construction and efficient in-place initialization of heterogeneous tuple elements.
     *
     * @tparam H Type of head element argument (deduced).
     * @tparam T Variadic types of tail element arguments (deduced).
     * @param[in,out] h Universal reference argument for head element initialization.
     * @param[in,out] t Universal reference arguments for tail element initialization.
     * @remark Employs `std::forward` to preserve lvalue/rvalue category per element.
     */
    template <typename H, typename... T>
    STuple(H&& h, T&&... t)
        : head(std::forward<H>(h)), tail(std::forward<T>(t)...) {}
};