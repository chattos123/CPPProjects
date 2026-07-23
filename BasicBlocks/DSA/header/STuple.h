/***********************************************************************
* File: STuple.h
* Description: Declares the templated STuple class similar to std::tuple.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include <utility>   // for std::forward
#include <cstddef>   // for size_t

/***********************************************************************
* Class: STuple<Ts...>
*
* Purpose: A generic container holding an arbitrary number of values.
***********************************************************************/
template <typename... Ts>
class DSALIB_API STuple;

// Recursive definition: head element + tail tuple
template <typename Head, typename... Tail>
class DSALIB_API STuple<Head, Tail...> {
public:
    Head head;
    STuple<Tail...> tail;

    STuple() = default;

    STuple(const Head& h, const Tail&... t)
        : head(h), tail(t...) {}

    template <typename H, typename... T>
    STuple(H&& h, T&&... t)
        : head(std::forward<H>(h)), tail(std::forward<T>(t)...) {}
};

// Base case: empty tuple
template <>
class DSALIB_API STuple<> {
public:
    STuple() = default;
};
