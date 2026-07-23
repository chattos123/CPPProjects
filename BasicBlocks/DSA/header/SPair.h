/***********************************************************************
* File: SPair.h
* Description: Declares the templated SPair class similar to std::pair.
***********************************************************************/
#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

/***********************************************************************
* Class: SPair<T1, T2>
*
* Purpose: A generic container holding two values (first, second).
***********************************************************************/
template <typename T1, typename T2>
class DSALIB_API SPair {
public:
    T1 first;
    T2 second;

    // Constructors
    SPair() : first(), second() {}
    SPair(const T1& a, const T2& b) : first(a), second(b) {}

    // Copy constructor
    SPair(const SPair& other) : first(other.first), second(other.second) {}

    // Move constructor
    SPair(SPair&& other) noexcept
        : first(std::move(other.first)), second(std::move(other.second)) {}

    // Assignment operators
    SPair& operator=(const SPair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }

    SPair& operator=(SPair&& other) noexcept {
        if (this != &other) {
            first = std::move(other.first);
            second = std::move(other.second);
        }
        return *this;
    }

    // Comparison operators
    bool operator==(const SPair& other) const {
        return first == other.first && second == other.second;
    }

    bool operator!=(const SPair& other) const {
        return !(*this == other);
    }

    bool operator<(const SPair& other) const {
        return (first < other.first) ||
               (!(other.first < first) && second < other.second);
    }

    bool operator>(const SPair& other) const {
        return other < *this;
    }

    bool operator<=(const SPair& other) const {
        return !(other < *this);
    }

    bool operator>=(const SPair& other) const {
        return !(*this < other);
    }
};

// Helper function like std::make_pair
template <typename T1, typename T2>
SPair<T1, T2> make_spair(T1 a, T2 b) {
    return SPair<T1, T2>(a, b);
}
