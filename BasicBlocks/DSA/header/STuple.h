#pragma once

#include "ExportMacro.h"
#include <utility>   // for std::forward
#include <cstddef>   // for size_t

// Forward declaration (NO DSALIB_API)
template <typename... Ts>
class STuple;

// Base case: empty tuple (NO DSALIB_API)
template <>
class STuple<> {
public:
    STuple() = default;
};

// Recursive definition: head element + tail tuple (NO DSALIB_API)
template <typename Head, typename... Tail>
class STuple<Head, Tail...> {
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