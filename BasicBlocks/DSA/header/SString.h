/**
 * @file SString.h
 * @brief Declaration of the immutable SString class for wide-character string handling.
 *
 * @author Soumyajit
 * @date 2026-07-22
 */

#pragma once

#include "ExportMacro.h"

#include <iostream>
#include <string>
#include <vector>
#include <cwchar>    // for std::wcscmp
#include <ostream>   // for std::ostream

/**
 * @class SString
 * @brief Immutable wide-character string class.
 */
class DSA_API SString {
private:
    wchar_t* Str;    ///< Internal wide-character buffer
    int str_len;     ///< Length of the string (excluding null terminator)

    void allocate_and_copy(const wchar_t* s);
    static void safe_copy(wchar_t* dest, const wchar_t* src, size_t max_len);
    static void safe_concat(wchar_t* dest, const wchar_t* src, size_t max_len);

public:
    /** @brief Default constructor: creates an empty string. */
    SString();

    /** @brief Constructs from a wide-character string. */
    explicit SString(const wchar_t* s);

    /** @brief Constructs from a narrow (char*) string by converting to wide characters. */
    explicit SString(const char* s);

    /** @brief Copy constructor. */
    SString(const SString& other);

    /** @brief Destructor: releases allocated memory. */
    ~SString();

    /** @brief Assignment operator from another SString. */
    SString& operator=(const SString& other);

    /** @brief Assignment operator from a wide-character string. */
    SString& operator=(const wchar_t* s);

    /** @brief Assignment operator from a narrow (char*) string. */
    SString& operator=(const char* strSource);

    /** @brief Subscript operator (read-only). */
    const wchar_t& operator[](int index) const;

    /** @brief Subscript operator (writable). */
    wchar_t& operator[](int index);

    /** @brief Returns the length of the string. */
    int length() const;

    /** @brief Returns the internal wide-character buffer. */
    const wchar_t* c_str() const;

    /** @brief Converts the internal wide string to a narrow UTF-8 C-style string. */
    const char* c_charString() const;

    /** @brief Returns an empty SString instance. */
    static SString Empty();

    /** @brief Returns a new string converted to uppercase. */
    SString to_upper() const;

    /** @brief Returns a new string converted to lowercase. */
    SString to_lower() const;

    /** @brief Returns a new string with case toggled for each character. */
    SString change_case() const;

    /** @brief Returns a new string with characters reversed. */
    SString revert() const;

    /** @brief Returns a substring of this SString. */
    SString substring(int start, int length) const;

    /** @brief Converts the internal wide-character buffer to a std::wstring. */
    std::wstring ToString() const;

    /** @brief Clears the contents of the string, resetting it to empty. */
    void Clear();

    // ---------------- Tokenize Overloads ----------------
    std::vector<SString> Tokenize(const wchar_t* delimiters = L" \t\n") const;
    std::vector<SString> Tokenize(const char* delimiters) const;
    std::vector<SString> Tokenize(const std::string& delimiters) const;
    std::vector<SString> Tokenize(const SString& delimiters) const;

    /** @brief Compares with another wide string. */
    bool match_string(const wchar_t* s) const;

    // ---------------- Static Helpers ----------------
    static bool IsEmpty(const SString& s);
    static bool IsNull(const SString& s);
    static bool IsNullOrEmpty(const SString& s);

    // ---------------- Concatenation Operators ----------------
    SString operator+(const SString& other) const;
    SString operator+(const wchar_t* s) const;
    SString operator+(const char* strSource) const;

    SString& operator+=(const wchar_t* strSource);
    SString& operator+=(const char* strSource);
    SString& operator+=(const SString& other);

       /** @brief Conversion operator to wide C-style string (const wchar_t*). Marked explicit to allow static_cast<std::wstring> */
    explicit operator const wchar_t*() const { return c_str(); }

    /** @brief Explicit conversion operator to narrow C-style string (const char*). */
    explicit operator const char*() const { return c_charString(); }

    /** @brief Explicit conversion operator to std::wstring. */
    explicit operator std::wstring() const { return ToString(); }

    /** @brief Explicit conversion operator to UTF-8 std::string. */
    explicit operator std::string() const { return ToUtf8(); }

    /** @brief Explicit conversion operator to int. */
    explicit operator int() const;

    /** @brief Explicit conversion operator to double. */
    explicit operator double() const;

    /** @brief Stream Operators */
    friend DSA_API std::wostream& operator<<(std::wostream& os, const SString& s);
    friend DSA_API std::wistream& operator>>(std::wistream& is, SString& s);

    /** @brief Creates an SString from a UTF-8 encoded string. */
    static SString FromUtf8(const char* utf8);

    /** @brief Converts the internal wide string to UTF-8 std::string. */
    std::string ToUtf8() const;

    // ---------------- STL Iterators ----------------
    using value_type = wchar_t;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    iterator begin() { return Str; }
    const_iterator begin() const { return Str; }

    iterator end() { return (Str ? Str + str_len : nullptr); }
    const_iterator end() const { return (Str ? Str + str_len : nullptr); }
};

// ---------------- Inline Non-Member Operators ----------------

inline bool operator==(const SString& lhs, const SString& rhs) {
    if (lhs.c_str() == nullptr || rhs.c_str() == nullptr) {
        return lhs.c_str() == rhs.c_str();
    }
    return std::wcscmp(lhs.c_str(), rhs.c_str()) == 0;
}

inline std::ostream& operator<<(std::ostream& os, const SString& s) {
    os << s.ToUtf8();
    return os;
}