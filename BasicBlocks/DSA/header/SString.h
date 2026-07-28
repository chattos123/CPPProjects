/**
 * @file SString.h
 * @brief Declaration of the custom SString class for wide-character and multi-byte string manipulation.
 * @author Soumyajit C
 * @date 2026-07-22
 * 
 * @remark Provides wide-character (`wchar_t`) string buffer management with UTF-8 conversion utilities,
 *         tokenization support, STL iterator compatibility, and cross-platform export macros.
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
 * @brief A wide-character (`wchar_t`) dynamic string wrapper providing rich manipulation primitives.
 * 
 * Manages dynamically allocated wide-character memory buffers. Supports constructors from both narrow (`char*`) 
 * and wide (`wchar_t*`) string inputs, explicit type conversions, case transformation, tokenization, 
 * concatenation operators, and C++ Standard Library iterator loops.
 */
class DSA_API SString {
private:
    wchar_t* Str;    ///< Pointer to the dynamically allocated internal wide-character null-terminated buffer.
    int str_len;     ///< Character count of the string, excluding the null terminator.

    /**
     * @brief Allocates dynamic heap storage and deep-copies the provided wide-character string.
     *
     * @param[in] s Pointer to the source wide-character string to copy.
     * @return void
     * @remark Internal utility for memory allocation and buffer initialization.
     */
    void allocate_and_copy(const wchar_t* s);

    /**
     * @brief Copies up to `max_len` wide characters safely from source to destination buffer.
     *
     * @param[out] dest Target wide-character memory buffer.
     * @param[in] src Source null-terminated wide-character string.
     * @param[in] max_len Maximum capacity limit of the destination buffer.
     * @return void
     * @remark Guarantees proper null-termination.
     */
    static void safe_copy(wchar_t* dest, const wchar_t* src, size_t max_len);

    /**
     * @brief Concatenates source wide characters onto the end of the destination buffer.
     *
     * @param[in,out] dest Target wide-character buffer containing existing string data.
     * @param[in] src Source wide-character string to append.
     * @param[in] max_len Total capacity boundary of the destination buffer.
     * @return void
     * @remark Ensures safe boundary bounds to prevent heap/stack buffer overruns.
     */
    static void safe_concat(wchar_t* dest, const wchar_t* src, size_t max_len);

public:
    /**
     * @brief Default constructor creating an empty SString instance.
     *
     * Initializes internal length to 0 and buffer to an empty wide string.
     *
     * @param None
     */
    SString();

    /**
     * @brief Explicit constructor initializing from a wide-character string buffer (`wchar_t*`).
     *
     * @param[in] s Pointer to null-terminated wide-character array.
     */
    explicit SString(const wchar_t* s);

    /**
     * @brief Explicit constructor initializing from a narrow character string (`char*`).
     *
     * Performs character-set widening conversion from narrow `char` to `wchar_t`.
     *
     * @param[in] s Pointer to null-terminated narrow character array.
     */
    explicit SString(const char* s);

    /**
     * @brief Copy constructor performing a deep memory copy of another SString instance.
     *
     * @param[in] other Source SString instance to duplicate.
     */
    SString(const SString& other);

    /**
     * @brief Destructor that deallocates internal wide-character dynamic buffer memory.
     *
     * @param None
     */
    ~SString();

    /**
     * @brief Copy assignment operator replacing contents with another SString.
     *
     * @param[in] other Source SString instance to copy.
     * @return SString& Reference to this updated SString instance.
     * @remark Protects against self-assignment.
     */
    SString& operator=(const SString& other);

    /**
     * @brief Assignment operator replacing contents with a null-terminated wide string.
     *
     * @param[in] s Pointer to null-terminated wide-character string.
     * @return SString& Reference to this updated SString instance.
     */
    SString& operator=(const wchar_t* s);

    /**
     * @brief Assignment operator replacing contents with a narrow character string.
     *
     * @param[in] strSource Pointer to null-terminated narrow character string.
     * @return SString& Reference to this updated SString instance.
     * @remark Performs internal character conversion to wide format.
     */
    SString& operator=(const char* strSource);

    /**
     * @brief Constant subscript operator for read-only element access.
     *
     * @param[in] index Zero-based character index to inspect.
     * @return const wchar_t& Constant reference to character at target index position.
     * @throws std::out_of_range If index parameter is negative or out of bounds (`index >= str_len`).
     */
    const wchar_t& operator[](int index) const;

    /**
     * @brief Subscript operator returning a mutable character reference.
     *
     * @param[in] index Zero-based character index to modify.
     * @return wchar_t& Mutable reference to wide character at target index position.
     * @throws std::out_of_range If index parameter is negative or out of bounds (`index >= str_len`).
     */
    wchar_t& operator[](int index);

    /**
     * @brief Retrieves the character count of the string, excluding null terminator.
     *
     * @param None
     * @return int Total number of wide characters in string.
     * @remark Query operates in O(1) time complexity.
     */
    int length() const;

    /**
     * @brief Accesses the internal raw null-terminated wide-character array (`wchar_t*`).
     *
     * @param None
     * @return const wchar_t* Immutable pointer to the wide-character buffer.
     */
    const wchar_t* c_str() const;

    /**
     * @brief Converts and returns internal wide-character string as a narrow C-style string.
     *
     * @param None
     * @return const char* Pointer to narrow C-style string representation.
     */
    const char* c_charString() const;

    /**
     * @brief Factory method returning an initialized empty SString instance.
     *
     * @param None
     * @return SString Static empty SString instance.
     */
    static SString Empty();

    /**
     * @brief Creates a copy of the string converted entirely to uppercase wide characters.
     *
     * @param None
     * @return SString New SString containing uppercase transformation.
     */
    SString to_upper() const;

    /**
     * @brief Creates a copy of the string converted entirely to lowercase wide characters.
     *
     * @param None
     * @return SString New SString containing lowercase transformation.
     */
    SString to_lower() const;

    /**
     * @brief Creates a copy of the string with inverted character casing (uppercase to lowercase and vice versa).
     *
     * @param None
     * @return SString New SString containing inverted case characters.
     */
    SString change_case() const;

    /**
     * @brief Creates a new string with character sequence completely reversed.
     *
     * @param None
     * @return SString Reversed SString instance.
     */
    SString revert() const;

    /**
     * @brief Extracts a substring given a starting offset index and length.
     *
     * @param[in] start Zero-based starting character position offset.
     * @param[in] length Total number of characters to copy into substring.
     * @return SString Extracted substring.
     * @throws std::out_of_range If start parameter exceeds string length bounds.
     */
    SString substring(int start, int length) const;

    /**
     * @brief Converts the internal wide-character buffer into a standard `std::wstring`.
     *
     * @param None
     * @return std::wstring Standard C++ wide string containing matching content.
     */
    std::wstring ToString() const;

    /**
     * @brief Resets string contents to an empty state and frees allocated dynamic memory.
     *
     * @param None
     * @return void
     */
    void Clear();

    // ---------------- Tokenize Overloads ----------------

    /**
     * @brief Splits string into tokens using wide-character delimiters.
     *
     * @param[in] delimiters Null-terminated wide string of delimiter characters (defaults to L" \t\n").
     * @return std::vector<SString> Vector of SString tokens separated by delimiters.
     */
    std::vector<SString> Tokenize(const wchar_t* delimiters = L" \t\n") const;

    /**
     * @brief Splits string into tokens using narrow character delimiters.
     *
     * @param[in] delimiters Null-terminated narrow string of delimiter characters.
     * @return std::vector<SString> Vector of SString tokens separated by delimiters.
     */
    std::vector<SString> Tokenize(const char* delimiters) const;

    /**
     * @brief Splits string into tokens using standard std::string delimiters.
     *
     * @param[in] delimiters Standard string containing delimiter characters.
     * @return std::vector<SString> Vector of SString tokens separated by delimiters.
     */
    std::vector<SString> Tokenize(const std::string& delimiters) const;

    /**
     * @brief Splits string into tokens using SString delimiters.
     *
     * @param[in] delimiters SString containing delimiter characters.
     * @return std::vector<SString> Vector of SString tokens separated by delimiters.
     */
    std::vector<SString> Tokenize(const SString& delimiters) const;

    /**
     * @brief Performs string comparison matching against a wide C-style string.
     *
     * @param[in] s Target wide string to compare against.
     * @return true If strings are identical character-by-character.
     * @return false If strings differ in length or content.
     */
    bool match_string(const wchar_t* s) const;

    // ---------------- Static Helpers ----------------

    /**
     * @brief Checks whether the given SString instance contains zero characters.
     *
     * @param[in] s Target SString reference to evaluate.
     * @return true If string length is 0.
     * @return false If string length is greater than 0.
     */
    static bool IsEmpty(const SString& s);

    /**
     * @brief Checks whether internal buffer pointer of the SString instance is null.
     *
     * @param[in] s Target SString reference to evaluate.
     * @return true If internal wide-character pointer is nullptr.
     * @return false If pointer references valid memory.
     */
    static bool IsNull(const SString& s);

    /**
     * @brief Checks whether target SString is either null or empty.
     *
     * @param[in] s Target SString reference to evaluate.
     * @return true If string buffer is null or contains zero characters.
     * @return false If string contains valid, non-empty character data.
     */
    static bool IsNullOrEmpty(const SString& s);

    // ---------------- Concatenation Operators ----------------

    /**
     * @brief Concatenates another SString onto the current string, returning a new result.
     *
     * @param[in] other Constant reference to SString to append.
     * @return SString Newly constructed string containing combined contents.
     */
    SString operator+(const SString& other) const;

    /**
     * @brief Concatenates a null-terminated wide string onto the current string.
     *
     * @param[in] s Wide-character array to append.
     * @return SString Newly constructed string containing combined contents.
     */
    SString operator+(const wchar_t* s) const;

    /**
     * @brief Concatenates a narrow character string onto the current string.
     *
     * @param[in] strSource Narrow character array to append.
     * @return SString Newly constructed string containing combined contents.
     */
    SString operator+(const char* strSource) const;

    /**
     * @brief Appends wide-character array in-place to this SString.
     *
     * @param[in] strSource Pointer to null-terminated wide character string to append.
     * @return SString& Reference to this updated SString instance.
     */
    SString& operator+=(const wchar_t* strSource);

    /**
     * @brief Appends narrow character array in-place to this SString.
     *
     * @param[in] strSource Pointer to null-terminated narrow character string to append.
     * @return SString& Reference to this updated SString instance.
     */
    SString& operator+=(const char* strSource);

    /**
     * @brief Appends another SString in-place to this instance.
     *
     * @param[in] other Reference to SString to append.
     * @return SString& Reference to this updated SString instance.
     */
    SString& operator+=(const SString& other);

    /**
     * @brief Explicit conversion operator to wide C-style string (`const wchar_t*`).
     *
     * Allows explicit casting (e.g., via `static_cast<const wchar_t*>`).
     *
     * @param None
     * @return const wchar_t* Pointer to internal wide-character string buffer.
     */
    explicit operator const wchar_t*() const { return c_str(); }

    /**
     * @brief Explicit conversion operator to narrow C-style string (`const char*`).
     *
     * @param None
     * @return const char* Pointer to converted narrow C-style string buffer.
     */
    explicit operator const char*() const { return c_charString(); }

    /**
     * @brief Explicit conversion operator to standard wide string (`std::wstring`).
     *
     * @param None
     * @return std::wstring Converted `std::wstring` instance.
     */
    explicit operator std::wstring() const { return ToString(); }

    /**
     * @brief Explicit conversion operator to UTF-8 encoded standard string (`std::string`).
     *
     * @param None
     * @return std::string UTF-8 encoded narrow string.
     */
    explicit operator std::string() const { return ToUtf8(); }

    /**
     * @brief Explicit conversion operator parsing numerical integer value from string.
     *
     * @param None
     * @return int Converted integer value.
     * @throws std::invalid_argument or std::out_of_range If conversion fails or numeric value overflows.
     */
    explicit operator int() const;

    /**
     * @brief Explicit conversion operator parsing floating-point double value from string.
     *
     * @param None
     * @return double Converted double-precision floating-point value.
     * @throws std::invalid_argument or std::out_of_range If conversion fails or value overflows double range.
     */
    explicit operator double() const;

    /**
     * @brief Stream output operator writing wide SString content to a wide output stream (`std::wostream`).
     *
     * @param[in,out] os Reference to destination wide output stream.
     * @param[in] s Constant reference to SString instance to stream.
     * @return std::wostream& Reference to output stream.
     */
    friend DSA_API std::wostream& operator<<(std::wostream& os, const SString& s);

    /**
     * @brief Stream input operator reading wide character sequence from input stream (`std::wistream`) into SString.
     *
     * @param[in,out] is Reference to wide input stream.
     * @param[out] s Reference to SString instance storing input stream characters.
     * @return std::wistream& Reference to input stream.
     */
    friend DSA_API std::wistream& operator>>(std::wistream& is, SString& s);

    /**
     * @brief Factory utility creating an SString from a narrow UTF-8 string buffer.
     *
     * @param[in] utf8 Pointer to null-terminated UTF-8 encoded narrow character string.
     * @return SString Constructed wide SString instance representing UTF-8 text.
     */
    static SString FromUtf8(const char* utf8);

    /**
     * @brief Encodes internal wide-character string into a UTF-8 narrow standard string (`std::string`).
     *
     * @param None
     * @return std::string Narrow UTF-8 encoded string.
     */
    std::string ToUtf8() const;

    // ---------------- STL Iterators ----------------
    using value_type = wchar_t;            ///< Type alias for stored character element value (`wchar_t`).
    using iterator = value_type*;          ///< Type alias for mutable random-access iterator.
    using const_iterator = const value_type*; ///< Type alias for constant read-only iterator.

    /**
     * @brief Returns a mutable iterator pointing to the beginning of the wide string buffer.
     *
     * @param None
     * @return iterator Pointer to the first character element.
     */
    iterator begin() { return Str; }

    /**
     * @brief Returns a constant iterator pointing to the beginning of the wide string buffer.
     *
     * @param None
     * @return const_iterator Constant pointer to the first character element.
     */
    const_iterator begin() const { return Str; }

    /**
     * @brief Returns a mutable iterator pointing past the end of the wide string buffer.
     *
     * @param None
     * @return iterator Pointer referencing position immediately past the final wide character element.
     */
    iterator end() { return (Str ? Str + str_len : nullptr); }

    /**
     * @brief Returns a constant iterator pointing past the end of the wide string buffer.
     *
     * @param None
     * @return const_iterator Constant pointer referencing position immediately past the final wide character element.
     */
    const_iterator end() const { return (Str ? Str + str_len : nullptr); }
};

// ---------------- Inline Non-Member Operators ----------------

/**
 * @brief Equality comparison operator testing if two SString instances contain identical wide-character sequences.
 *
 * @param[in] lhs Left-hand operand SString.
 * @param[in] rhs Right-hand operand SString.
 * @return true If strings are identical or both internal pointers are nullptr.
 * @return false If string contents or lengths differ.
 */
inline bool operator==(const SString& lhs, const SString& rhs) {
    if (lhs.c_str() == nullptr || rhs.c_str() == nullptr) {
        return lhs.c_str() == rhs.c_str();
    }
    return std::wcscmp(lhs.c_str(), rhs.c_str()) == 0;
}

/**
 * @brief Stream output operator streaming narrow UTF-8 representation of SString to narrow stream (`std::ostream`).
 *
 * @param[in,out] os Reference to target narrow output stream.
 * @param[in] s Constant reference to SString instance to write.
 * @return std::ostream& Reference to narrow output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const SString& s) {
    os << s.ToUtf8();
    return os;
}