#pragma once
#include "STuple.h"

// Recursive getter
template <std::size_t Index, typename Head, typename... Tail>
auto& get(STuple<Head, Tail...>& tuple) {
    if constexpr (Index == 0) {
        return tuple.head;
    } else {
        return get<Index - 1>(tuple.tail);
    }
}

template <std::size_t Index, typename Head, typename... Tail>
const auto& get(const STuple<Head, Tail...>& tuple) {
    if constexpr (Index == 0) {
        return tuple.head;
    } else {
        return get<Index - 1>(tuple.tail);
    }
}
