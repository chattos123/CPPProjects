/**
 * @file SString.h
 * @brief Declaration of the immutable SString class for wide-character string handling.
 *
 * The SString class provides an immutable string type similar to Java's String or MFC's CString.
 * Internally it stores data as wide characters (wchar_t) for Unicode support.
 * All operations return new SString objects, ensuring immutability.
 *
 * Features:
 * - Construction from wide strings or UTF-8 strings
 * - Case conversion (upper, lower, toggle case)
 * - String reversal
 * - Concatenation
 * - UTF-8 <-> UTF-16 conversion utilities
 * - Stream input/output operators
 *
 * @author Soumyajit
 * @date 2026-07-22
 */

#pragma once

#ifdef DSALIB_EXPORTS
#define DSALIB_API __declspec(dllexport)
#else
#define DSALIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <string>

/**
 * @class SString
 * @brief Immutable wide-character string class.
 *
 * Provides safe, immutable string operations on wchar_t buffers.
 * All modifying operations return new SString instances.
 */
class DSALIB_API SString {
private:
    wchar_t* Str;   ///< Internal wide-character buffer
    int str_len;    ///< Length of the string (excluding null terminator)

    /**
     * @brief Allocates memory and copies the given wide string safely.
     * @param s Input wide string to copy.
     */
    void allocate_and_copy(const wchar_t* s);

    /**
     * @brief Safely copies a wide string into a destination buffer.
     * @param dest Destination buffer.
     * @param src Source wide string.
     * @param max_len Maximum number of characters (including null terminator).
     */
    static void safe_copy(wchar_t* dest, const wchar_t* src, size_t max_len);

    /**
     * @brief Safely concatenates a wide string onto a destination buffer.
     * @param dest Destination buffer (must be large enough).
     * @param src Source wide string.
     * @param max_len Maximum number of characters (including null terminator).
     */
    static void safe_concat(wchar_t* dest, const wchar_t* src, size_t max_len);

public:
    /** @brief Default constructor: creates an empty string. */
    SString();

    /** @brief Constructs from a wide-character string. */
    explicit SString(const wchar_t* s);

    /** 
     * @brief Constructs from a narrow (char*) string by converting to wide characters.
     * @param s Narrow string (UTF-8 or ASCII).
     */
    explicit SString(const char* s);


    /** @brief Copy constructor. */
    SString(const SString& other);

    /** @brief Assignment operator from another SString. */
    SString& operator=(const SString& other);

    /** @brief Assignment operator from a wide-character string. */
    SString& operator=(const wchar_t* s);

    /**
     * @brief Assignment operator from a narrow (char*) string.
     * Internally converts to wide characters before storing.
     * @param strSource Narrow string (UTF-8 or ASCII).
     * @return Reference to this SString after assignment.
     */
    SString& operator=(const char* strSource);

    /**
     * @brief Provides read-only access to a character at the given index.
     * @param index Position of the character (0-based).
     * @return Const reference to the wchar_t at the given index.
     * @throws std::out_of_range if index is invalid.
     */
    const wchar_t& operator[](int index) const;

    /**
     * @brief Provides writable access to a character at the given index.
     * @param index Position of the character (0-based).
     * @return Reference to the wchar_t at the given index.
     * @throws std::out_of_range if index is invalid.
     */
    wchar_t& operator[](int index);



    /** @brief Destructor: releases allocated memory. */
    ~SString();

    /** @brief Returns the length of the string. */
    int length() const;

    /** @brief Returns the internal wide-character buffer. */
    const wchar_t* c_str() const;

        /**
     * @brief Converts the internal wide-character string to a narrow UTF-8 C-style string.
     * @return Pointer to a UTF-8 encoded char buffer (null-terminated).
     *
     * @note The returned pointer is valid until the next call to c_charString().
     *       Internally managed buffer; do not free it manually.
     */
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

        /**
     * @brief Returns a substring of this SString.
     * @param start Starting index (0-based).
     * @param length Number of characters to extract.
     * @return New SString containing the requested substring.
     * @throws std::out_of_range if start or length are invalid.
     */
    SString substring(int start, int length) const;

    /**
     * @brief Converts the internal wide-character buffer to a std::wstring.
     * @return A std::wstring containing the same characters.
     */
    std::wstring ToString() const;


    /**
     * @brief Clears the contents of the string, resetting it to empty.
     */
    void Clear();



    /**
     * @brief Compares with another wide string.
     * @param s Wide string to compare.
     * @return true if equal, false otherwise.
     */
    bool match_string(const wchar_t* s) const;

    /** @brief Concatenates with another SString. */
    SString operator+(const SString& other) const;

    /** @brief Concatenates with a wide-character string. */
    SString operator+(const wchar_t* s) const;

        /** 
     * @brief Concatenates with a narrow (char*) string.
     * @param strSource Narrow string (UTF-8 or ASCII).
     * @return New SString containing the concatenation.
     */
    SString operator+(const char* strSource) const;

        /** 
     * @brief Appends a wide-character string to this SString.
     * @param strSource Wide string to append.
     * @return Reference to this SString after concatenation.
     */
    SString& operator+=(const wchar_t* strSource);

    /** 
     * @brief Appends a narrow (char*) string to this SString.
     * Internally converts to wide characters before appending.
     * @param strSource Narrow string (UTF-8 or ASCII).
     * @return Reference to this SString after concatenation.
     */
    SString& operator+=(const char* strSource);

        /** 
     * @brief Appends another SString to this instance.
     * @param other The SString to append.
     * @return Reference to this SString after concatenation.
     */
    SString& operator+=(const SString& other);




    /** @brief Output stream operator. */
    DSALIB_API friend std::wostream& operator<<(std::wostream& os, const SString& s);

    /** @brief Input stream operator. */
    DSALIB_API friend std::wistream& operator>>(std::wistream& is, SString& s);

    /** @brief Creates an SString from a UTF-8 encoded string. */
    static SString FromUtf8(const char* utf8);

    /** @brief Converts the internal wide string to UTF-8. */
    std::string ToUtf8() const;
};
