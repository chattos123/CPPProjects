/**
 * @file STupleGet.h
 * @brief Helper utility functions providing compile-time indexed element access for STuple instances.
 * @author Soumyajit C
 * @date 2026
 * 
 * @remark Implements `get<Index>()` overloads using C++17 `if constexpr` compile-time conditional branch 
 *         evaluation to recursively traverse nested STuple structures without runtime recursion overhead.
 */

#pragma once

#include "ExportMacro.h"
#include "STuple.h"

/**
 * @brief Accesses a mutable reference to the element at compile-time position `Index` within an STuple.
 *
 * Uses C++17 `if constexpr` to unwrapping nested tuple tail structures at compile time until `Index == 0`.
 *
 * @tparam Index Zero-based compile-time element position index to access.
 * @tparam Head Type of the head element at the current tuple recursion level (deduced).
 * @tparam Tail Variadic pack of remaining element types at the current tuple level (deduced).
 * @param[in,out] tuple Reference to the target `STuple` instance from which to extract the element.
 * @return auto& Mutable reference to the element stored at index `Index`.
 * @remark Zero runtime performance cost due to compile-time template instantiation and inline expansion.
 */
template <std::size_t Index, typename Head, typename... Tail>
auto& get(STuple<Head, Tail...>& tuple)
 {
    if constexpr (Index == 0) 
    {
        return tuple.head;
    } 
    else 
    {
        return get<Index - 1>(tuple.tail);
    }
}

/**
 * @brief Accesses an immutable (const) reference to the element at compile-time position `Index` within an STuple.
 *
 * Provides read-only access for constant `STuple` references.
 *
 * @tparam Index Zero-based compile-time element position index to access.
 * @tparam Head Type of the head element at the current tuple recursion level (deduced).
 * @tparam Tail Variadic pack of remaining element types at the current tuple level (deduced).
 * @param[in] tuple Immutable reference to the target constant `STuple` instance.
 * @return const auto& Immutable reference to the element stored at index `Index`.
 * @remark Zero runtime performance cost due to compile-time template instantiation and inline expansion.
 */
template <std::size_t Index, typename Head, typename... Tail>
const auto& get(const STuple<Head, Tail...>& tuple) 
{
    if constexpr (Index == 0) 
    {
        return tuple.head;
    } 
    else 
    {
        return get<Index - 1>(tuple.tail);
    }
}