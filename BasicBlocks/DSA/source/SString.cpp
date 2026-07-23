/**
 * @file SString.cpp
 * @brief Implementation of the immutable SString class.
 *
 * Provides definitions for constructors, operators, and utility functions
 * for wide-character string handling and UTF-8/UTF-16 conversion.
 */

#include "SString.h"
#include <cwchar>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#include <cstring>
#endif

// ---------------- Private Helper ----------------

/**
 * @brief Allocates dynamic memory for the wide-character buffer and copies the source string.
 *
 * @param[in] strSource Pointer to the null-terminated source wide string. If nullptr, allocates an empty string buffer.
 *
 * @remarks If `strSource` is null, allocating a 1-element buffer ensures `Str` is never a nullptr.
 */
void SString::allocate_and_copy(const wchar_t* strSource)
{
    if (strSource)
    {
        str_len = std::wcslen(strSource);
        Str = new wchar_t[str_len + 1];
        safe_copy(Str, strSource, str_len + 1);
    }
    else
    {
        str_len = 0;
        Str = new wchar_t[1];
        Str[0] = L'\0';
    }
}

/**
 * @brief Safely copies wide characters from a source buffer to a destination buffer.
 *
 * @param[out] dest Pointer to the destination wide-character buffer.
 * @param[in] src Pointer to the null-terminated source wide string.
 * @param[in] max_len Maximum number of wide characters (including the null terminator) allowed in `dest`.
 *
 * @remarks Guarantees null-termination as long as `max_len > 0`. Safe against buffer overflows.
 */
void SString::safe_copy(wchar_t* dest, const wchar_t* src, size_t max_len)
{
    if (!dest || !src || max_len == 0)
    { 
        return;
    }
    else
    {
        size_t i = 0;

        while (i < max_len - 1 && src[i] != L'\0')
        {
            dest[i] = src[i];
            i++;
        }

        dest[i] = L'\0';
    }
}

/**
 * @brief Safely concatenates a source wide string to the end of a destination wide buffer.
 *
 * @param[in,out] dest Pointer to the null-terminated destination wide buffer.
 * @param[in] src Pointer to the null-terminated source wide string.
 * @param[in] max_len Maximum capacity of the destination buffer in wide characters.
 *
 * @remarks Respects `max_len` limits to prevent buffer overflow and ensures the result is always null-terminated.
 */
void SString::safe_concat(wchar_t* dest, const wchar_t* src, size_t max_len)
{
    if (!dest || !src || max_len == 0) return;

    size_t dlen = std::wcslen(dest);
    size_t i = 0;
    while (dlen + i < max_len - 1 && src[i] != L'\0')
    {
        dest[dlen + i] = src[i];
        i++;
    }

    dest[dlen + i] = L'\0';
}

// ---------------- Constructors ----------------

/**
 * @brief Default constructor. Initializes an empty `SString`.
 *
 * @remarks Allocates a 1-element buffer containing L'\0' and sets `str_len` to 0.
 */
SString::SString() : Str(new wchar_t[1]), str_len(0)
{
    Str[0] = L'\0';
}

/**
 * @brief Constructs an `SString` from a null-terminated wide-character string.
 *
 * @param[in] s Pointer to a null-terminated `wchar_t` array. Can be nullptr.
 */
SString::SString(const wchar_t* s)
{
    allocate_and_copy(s);
}

// ---------------- Constructor from char* ----------------

/**
 * @brief Constructs an `SString` by converting a UTF-8 encoded narrow string to wide characters.
 *
 * @param[in] strSource Pointer to a null-terminated UTF-8 encoded `char` string. Can be nullptr.
 *
 * @remarks On Windows, uses `MultiByteToWideChar`. On POSIX platforms, uses `iconv`. If allocation or conversion fails, defaults to an empty string.
 */
SString::SString(const char* strSource) 
{
    if (!strSource)
    {
        str_len = 0;
        Str = new wchar_t[1];
        Str[0] = L'\0';
        return;
    }

#ifdef _WIN32
    // Windows: use MultiByteToWideChar
    int len = MultiByteToWideChar(CP_UTF8, 0, strSource, -1, nullptr, 0);
    std::wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, strSource, -1, &ws[0], len);
    str_len = ws.length();
    Str = new wchar_t[str_len + 1];
    safe_copy(Str, ws.c_str(), str_len + 1);
#else
    // POSIX: use iconv
    iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
    if (cd == (iconv_t)-1) {
        str_len = 0;
        Str = new wchar_t[1];
        Str[0] = L'\0';
        return;
    }

    size_t inBytes = std::strlen(strSource);
    size_t outBytes = (inBytes + 1) * sizeof(wchar_t);
    std::wstring ws;
    ws.resize(inBytes + 1);

    char* inBuf = const_cast<char*>(strSource);
    char* outBuf = reinterpret_cast<char*>(&ws[0]);
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    str_len = std::wcslen(ws.c_str());
    Str = new wchar_t[str_len + 1];
    safe_copy(Str, ws.c_str(), str_len + 1);
#endif
}

/**
 * @brief Copy constructor. Creates a deep copy of another `SString`.
 *
 * @param[in] other Reference to the `SString` instance to copy.
 */
SString::SString(const SString& other) {
    allocate_and_copy(other.Str);
}

// ---------------- Assignment ----------------

/**
 * @brief Copy assignment operator. Performs a deep copy from another `SString`.
 *
 * @param[in] other Reference to the `SString` to copy from.
 * @return SString& Reference to this instance (*this).
 *
 * @remarks Includes a self-assignment guard (`this != &other`).
 */
SString& SString::operator=(const SString& other) 
{
    if (this != &other)
    {
        delete[] Str;
        allocate_and_copy(other.Str);
    }

    return *this;
}

/**
 * @brief Replaces the current string content with a null-terminated wide string.
 *
 * @param[in] s Pointer to a null-terminated wide string.
 * @return SString& Reference to this instance (*this).
 */
SString& SString::operator=(const wchar_t* s) {
    delete[] Str;
    allocate_and_copy(s);
    return *this;
}

/**
 * @brief Replaces the current string content with a UTF-8 encoded narrow string.
 *
 * @param[in] strSource Pointer to a null-terminated UTF-8 character string.
 * @return SString& Reference to this instance (*this).
 *
 * @remarks Converts input from UTF-8 to wide characters via `MultiByteToWideChar` (Windows) or `iconv` (POSIX).
 */
SString& SString::operator=(const char* strSource)
{
    // Free old buffer
    delete[] Str;
    Str = nullptr;
    str_len = 0;

    if (!strSource) {
        Str = new wchar_t[1];
        Str[0] = L'\0';
        return *this;
    }

#ifdef _WIN32
    // Windows: convert UTF-8 char* to wide string
    int len = MultiByteToWideChar(CP_UTF8, 0, strSource, -1, nullptr, 0);
    std::wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, strSource, -1, &ws[0], len);

    str_len = static_cast<int>(ws.length());
    Str = new wchar_t[str_len + 1];
    safe_copy(Str, ws.c_str(), str_len + 1);
#else
    // POSIX: use iconv
    iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
    if (cd == (iconv_t)-1) {
        Str = new wchar_t[1];
        Str[0] = L'\0';
        return *this;
    }

    size_t inBytes = std::strlen(strSource);
    size_t outBytes = (inBytes + 1) * sizeof(wchar_t);
    std::wstring ws;
    ws.resize(inBytes + 1);

    char* inBuf = const_cast<char*>(strSource);
    char* outBuf = reinterpret_cast<char*>(&ws[0]);
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    str_len = static_cast<int>(std::wcslen(ws.c_str()));
    Str = new wchar_t[str_len + 1];
    safe_copy(Str, ws.c_str(), str_len + 1);
#endif

    return *this;
}

// ---------------- Destructor ----------------

/**
 * @brief Destructor. Deallocates the internal character buffer.
 *
 * @remarks Frees the memory allocated for `Str` using `delete[]` and resets the pointer to nullptr.
 */
SString::~SString() {
    delete[] Str;
    Str = nullptr;
}

// ---------------- Accessors ----------------

/**
 * @brief Gets the length of the string in characters (excluding the null terminator).
 *
 * @return int Number of wide characters in the string.
 */
int SString::length() const { return str_len; }

/**
 * @brief Returns a raw pointer to the internal wide-character string buffer.
 *
 * @return const wchar_t* Pointer to the null-terminated wide string.
 *
 * @remarks The returned pointer is owned by `SString` and must not be deleted by the caller.
 */
const wchar_t* SString::c_str() const { return Str; }

/**
 * @brief Converts and returns the string as a UTF-8 encoded narrow C-string.
 *
 * @return const char* Pointer to an internal static UTF-8 buffer containing the converted string.
 *
 * @remarks **Thread-Safety Warning:** Uses an internal `static` buffer that persists across calls. Concurrent calls or subsequent invocations will overwrite previous buffer contents.
 */
const char* SString::c_charString() const {
#ifdef _WIN32
    // Windows: use WideCharToMultiByte
    int len = WideCharToMultiByte(CP_UTF8, 0, Str, -1, nullptr, 0, nullptr, nullptr);

    // static buffer persists across calls
    static char* buffer = nullptr;
    static size_t bufferSize = 0;

    // reallocate if needed
    if (len > static_cast<int>(bufferSize)) {
        delete[] buffer;
        bufferSize = len + 1;
        buffer = new char[bufferSize];
    }

    WideCharToMultiByte(CP_UTF8, 0, Str, -1, buffer, bufferSize, nullptr, nullptr);
    return buffer;
#else
    // POSIX: use iconv
    static char* buffer = nullptr;
    static size_t bufferSize = 0;

    iconv_t cd = iconv_open("UTF-8", "WCHAR_T");
    if (cd == (iconv_t)-1) return "";

    size_t inBytes = (std::wcslen(Str) + 1) * sizeof(wchar_t);
    size_t outBytes = inBytes * 4; // worst case

    if (outBytes > bufferSize) {
        delete[] buffer;
        bufferSize = outBytes;
        buffer = new char[bufferSize];
    }

    char* inBuf = reinterpret_cast<char*>(Str);
    char* outBuf = buffer;
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    return buffer;
#endif
}

// ---------------- Factory ----------------

/**
 * @brief Factory method that returns an empty `SString` instance.
 *
 * @return SString An empty `SString` object.
 */
SString SString::Empty() { return SString(); }

/**
 * @brief Resets the string to an empty state and frees allocated memory.
 *
 * @remarks Deallocates existing character memory and reallocates a minimal 1-element buffer containing L'\0'.
 */
void SString::Clear() {
    delete[] Str;          // free old buffer
    Str = new wchar_t[1];  // allocate new buffer with just null terminator
    Str[0] = L'\0';
    str_len = 0;
}

/**
 * @brief Converts the instance into a standard `std::wstring`.
 *
 * @return std::wstring A `std::wstring` copy of the underlying string data.
 */
std::wstring SString::ToString() const {
    return std::wstring(Str, str_len);
}

/**
 * @brief Extracts a substring from the current string.
 *
 * @param[in] start Zero-based starting index of the substring.
 * @param[in] length Number of wide characters to include in the substring.
 * @return SString A new `SString` containing the specified range.
 *
 * @throws std::out_of_range Thrown if `start` or `length` fall outside string bounds.
 */
SString SString::substring(int start, int length) const 
{
    if (start < 0 || start >= str_len) {
        throw std::out_of_range("SString::substring start index out of range");
    }
    if (length < 0 || start + length > str_len) {
        throw std::out_of_range("SString::substring length out of range");
    }

    wchar_t* buffer = new wchar_t[length + 1];
    for (int i = 0; i < length; i++) {
        buffer[i] = Str[start + i];
    }
    buffer[length] = L'\0';

    SString result(buffer);
    delete[] buffer;
    buffer = nullptr;
    return result;
}

// ---------------- Case Conversions ----------------

/**
 * @brief Creates a new string with all wide characters converted to uppercase.
 *
 * @return SString A new uppercase `SString` instance.
 *
 * @remarks Uses `std::towupper` internally for locale-aware conversion.
 */
SString SString::to_upper() const
{
    SString result(*this);
    for (int i = 0; i < result.str_len; i++)
        result.Str[i] = std::towupper(result.Str[i]);
    return result;
}

/**
 * @brief Creates a new string with all wide characters converted to lowercase.
 *
 * @return SString A new lowercase `SString` instance.
 *
 * @remarks Uses `std::towlower` internally for locale-aware conversion.
 */
SString SString::to_lower() const
{
    SString result(*this);
    for (int i = 0; i < result.str_len; i++)
        result.Str[i] = std::towlower(result.Str[i]);
    return result;
}

/**
 * @brief Toggles character cases (uppercase becomes lowercase, and vice versa).
 *
 * @return SString A new `SString` with inverted character casing.
 */
SString SString::change_case() const 
{
    SString result(*this);
    for (int i = 0; i < result.str_len; i++) {
        if (std::iswlower(result.Str[i]))
            result.Str[i] = std::towupper(result.Str[i]);
        else if (std::iswupper(result.Str[i]))
            result.Str[i] = std::towlower(result.Str[i]);
    }
    return result;
}

/**
 * @brief Creates a reversed copy of the string.
 *
 * @return SString A new `SString` with characters in reverse order.
 *
 * @remarks Reverses raw code units (`wchar_t`), which may split multi-word code points or surrogate pairs.
 */
SString SString::revert() const 
{
    SString result(*this);
    for (int i = 0; i < result.str_len / 2; i++)
        std::swap(result.Str[i], result.Str[result.str_len - i - 1]);
    return result;
}

/**
 * @brief Splits the string into substrings using wide-character delimiters.
 *
 * @param[in] delimiters Pointer to a null-terminated wide string containing delimiter characters.
 * @return std::vector<SString> A list of extracted tokens.
 *
 * @remarks Skips consecutive delimiters; empty tokens are not added to the result vector.
 */
std::vector<SString> SString::Tokenize(const wchar_t* delimiters) const 
{
    std::vector<SString> tokens;
    std::wstring ws(Str);

    size_t start = 0;
    size_t pos = 0;

    while ((pos = ws.find_first_of(delimiters, start)) != std::wstring::npos) {
        if (pos > start) {
            tokens.emplace_back(ws.substr(start, pos - start).c_str());
        }
        start = pos + 1;
    }

    if (start < ws.length()) {
        tokens.emplace_back(ws.substr(start).c_str());
    }

    return tokens;
}

/**
 * @brief Helper function to convert a narrow string delimiter into a wide string.
 *
 * @param[in] delimiters Pointer to a null-terminated UTF-8 or ASCII string of delimiters.
 * @return std::wstring Wide-character string containing the converted delimiters.
 */
static std::wstring convertDelimiters(const char* delimiters)
{
#ifdef _WIN32
    int len = MultiByteToWideChar(CP_UTF8, 0, delimiters, -1, nullptr, 0);
    std::wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, delimiters, -1, &ws[0], len);
    return ws;
#else
    // Simplified for POSIX: assume ASCII
    std::wstring ws;
    while (*delimiters) {
        ws.push_back(static_cast<wchar_t>(*delimiters));
        ++delimiters;
    }
    return ws;
#endif
}

/**
 * @brief Splits the string into substrings using C-string delimiters.
 *
 * @param[in] delimiters Pointer to a null-terminated string containing delimiter characters.
 * @return std::vector<SString> A list of extracted tokens.
 */
std::vector<SString> SString::Tokenize(const char* delimiters) const 
{
    std::wstring wsDelims = convertDelimiters(delimiters);
    std::vector<SString> tokens;
    std::wstring ws(Str);

    size_t start = 0;
    size_t pos = 0;

    while ((pos = ws.find_first_of(wsDelims, start)) != std::wstring::npos) {
        if (pos > start) {
            tokens.emplace_back(ws.substr(start, pos - start).c_str());
        }
        start = pos + 1;
    }

    if (start < ws.length()) {
        tokens.emplace_back(ws.substr(start).c_str());
    }

    return tokens;
}

/**
 * @brief Splits the string into substrings using standard string delimiters.
 *
 * @param[in] delimiters `std::string` containing delimiter characters.
 * @return std::vector<SString> A list of extracted tokens.
 */
std::vector<SString> SString::Tokenize(const std::string delimiters) const 
{
    return Tokenize(delimiters.c_str());
}

/**
 * @brief Splits the string into substrings using `SString` delimiters.
 *
 * @param[in] delimiters `SString` object containing delimiter characters.
 * @return std::vector<SString> A list of extracted tokens.
 */
std::vector<SString> SString::Tokenize(const SString delimiters) const 
{
    std::vector<SString> tokens;
    std::wstring ws(Str);
    std::wstring wsDelims(delimiters.c_str());

    size_t start = 0;
    size_t pos = 0;

    while ((pos = ws.find_first_of(wsDelims, start)) != std::wstring::npos) {
        if (pos > start) {
            tokens.emplace_back(ws.substr(start, pos - start).c_str());
        }
        start = pos + 1;
    }

    if (start < ws.length()) {
        tokens.emplace_back(ws.substr(start).c_str());
    }

    return tokens;
}

// ---------------- Comparison ----------------

/**
 * @brief Checks if the string exactly matches a given wide C-string.
 *
 * @param[in] s Pointer to the null-terminated wide string to compare against.
 * @return true If strings are identical (`std::wcscmp` returns 0).
 * @return false Otherwise.
 */
bool SString::match_string(const wchar_t* s) const 
{
    return std::wcscmp(Str, s) == 0;
}

// statics

/**
 * @brief Checks if an `SString` instance is empty (length == 0).
 *
 * @param[in] s Reference to the `SString` instance to test.
 * @return true If the string length is 0.
 * @return false Otherwise.
 */
bool SString::IsEmpty(const SString& s) {
    return s.str_len == 0;
}

/**
 * @brief Checks if the internal character buffer pointer of an `SString` is null.
 *
 * @param[in] s Reference to the `SString` instance to test.
 * @return true If `Str` is nullptr.
 * @return false Otherwise.
 */
bool SString::IsNull(const SString& s) {
    return s.Str == nullptr;
}

/**
 * @brief Checks whether an `SString` instance is null or has zero length.
 *
 * @param[in] s Reference to the `SString` instance to test.
 * @return true If `Str` is nullptr or length is 0.
 * @return false Otherwise.
 */
bool SString::IsNullOrEmpty(const SString& s) {
    return (s.Str == nullptr) || (s.str_len == 0);
}

// ---------------- Concatenation ----------------

/**
 * @brief Concatenates two `SString` objects and returns the combined result.
 *
 * @param[in] other The right-hand side `SString` operand.
 * @return SString A new `SString` instance containing the concatenated string.
 */
SString SString::operator+(const SString& other) const
{
    wchar_t* buffer = new wchar_t[str_len + other.str_len + 1];
    safe_copy(buffer, Str, str_len + other.str_len + 1);
    safe_concat(buffer, other.Str, str_len + other.str_len + 1);
    SString result(buffer);
    delete[] buffer;
    return result;
}

/**
 * @brief Concatenates a wide C-string onto the current `SString`.
 *
 * @param[in] s Null-terminated wide string to append.
 * @return SString A new `SString` instance containing the concatenated result.
 */
SString SString::operator+(const wchar_t* s) const
{
    int new_len = str_len + std::wcslen(s);
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, s, new_len + 1);
    SString result(buffer);
    delete[] buffer;
    return result;
}

/**
 * @brief Concatenates a UTF-8 narrow string onto the current `SString`.
 *
 * @param[in] strSource Null-terminated UTF-8 encoded string to append.
 * @return SString A new `SString` instance containing the concatenated result.
 *
 * @remarks Converts `strSource` to wide characters before concatenation.
 */
SString SString::operator+(const char* strSource) const
{
    if (!strSource)
    {
        return *this; // nothing to add
    }

#ifdef _WIN32
    // Convert char* (UTF-8) to wide string
    int len = MultiByteToWideChar(CP_UTF8, 0, strSource, -1, nullptr, 0);
    std::wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, strSource, -1, &ws[0], len);

    int new_len = str_len + static_cast<int>(ws.length());
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, ws.c_str(), new_len + 1);

    SString result(buffer);
    delete[] buffer;
    buffer =  nullptr;
    return result;
#else
    // POSIX: use iconv to convert char* to wchar_t*
    iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
    if (cd == (iconv_t)-1) return *this;

    size_t inBytes = std::strlen(strSource);
    size_t outBytes = (inBytes + 1) * sizeof(wchar_t);
    std::wstring ws;
    ws.resize(inBytes + 1);

    char* inBuf = const_cast<char*>(strSource);
    char* outBuf = reinterpret_cast<char*>(&ws[0]);
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    int new_len = str_len + static_cast<int>(std::wcslen(ws.c_str()));
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, ws.c_str(), new_len + 1);

    SString result(buffer);
    delete[] buffer;
    return result;
#endif
}

/**
 * @brief Appends a wide string to this string instance in-place.
 *
 * @param[in] strSource Pointer to the null-terminated wide string to append.
 * @return SString& Reference to this modified instance (*this).
 */
SString& SString::operator+=(const wchar_t* strSource)
{
    if (!strSource) return *this;

    int new_len = str_len + std::wcslen(strSource);
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, strSource, new_len + 1);

    delete[] Str;
    Str = buffer;
    str_len = new_len;
    return *this;
}

/**
 * @brief Appends a UTF-8 narrow string to this string instance in-place.
 *
 * @param[in] strSource Pointer to the null-terminated UTF-8 string to append.
 * @return SString& Reference to this modified instance (*this).
 */
SString& SString::operator+=(const char* strSource)
{
    if (!strSource) return *this;

#ifdef _WIN32
    // Convert char* (UTF-8) to wide string
    int len = MultiByteToWideChar(CP_UTF8, 0, strSource, -1, nullptr, 0);
    std::wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, strSource, -1, &ws[0], len);

    int new_len = str_len + static_cast<int>(ws.length());
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, ws.c_str(), new_len + 1);

    delete[] Str;
    Str = nullptr;
    Str = buffer;
    str_len = new_len;
    return *this;
#else
    // POSIX: use iconv
    iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
    if (cd == (iconv_t)-1) return *this;

    size_t inBytes = std::strlen(strSource);
    size_t outBytes = (inBytes + 1) * sizeof(wchar_t);
    std::wstring ws;
    ws.resize(inBytes + 1);

    char* inBuf = const_cast<char*>(strSource);
    char* outBuf = reinterpret_cast<char*>(&ws[0]);
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    int new_len = str_len + static_cast<int>(std::wcslen(ws.c_str()));
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, ws.c_str(), new_len + 1);

    delete[] Str;
    Str = buffer;
    str_len = new_len;
    return *this;
#endif
}

/**
 * @brief Appends another `SString` instance to this string in-place.
 *
 * @param[in] other Reference to the `SString` object to append.
 * @return SString& Reference to this modified instance (*this).
 */
SString& SString::operator+=(const SString& other) 
{
    if (other.str_len == 0) return *this;

    int new_len = str_len + other.str_len;
    wchar_t* buffer = new wchar_t[new_len + 1];
    safe_copy(buffer, Str, new_len + 1);
    safe_concat(buffer, other.Str, new_len + 1);

    delete[] Str;
    Str = nullptr;
    Str = buffer;
    str_len = new_len;
    return *this;
}

/**
 * @brief Accesses a character at the specified index for read-only operations.
 *
 * @param[in] index Zero-based index of the wide character.
 * @return const wchar_t& Const reference to the character at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= str_len`.
 */
const wchar_t& SString::operator[](int index) const {
    if (index < 0 || index >= str_len) {
        throw std::out_of_range("SString index out of range");
    }
    return Str[index];
}

/**
 * @brief Accesses a character at the specified index for modification.
 *
 * @param[in] index Zero-based index of the wide character.
 * @return wchar_t& Reference to the character at `index`.
 *
 * @throws std::out_of_range Thrown if `index < 0` or `index >= str_len`.
 * @remarks **Note:** While `SString` is documented as immutable, this operator enables direct element modification.
 */
wchar_t& SString::operator[](int index) {
    if (index < 0 || index >= str_len) {
        throw std::out_of_range("SString index out of range");
    }
    return Str[index];
}

// ---------------- Stream Operators ----------------

/**
 * @brief Stream insertion operator for wide output streams.
 *
 * @param[in,out] os Wide output stream object.
 * @param[in] s `SString` object to write to the stream.
 * @return std::wostream& Reference to the stream (`os`).
 */
std::wostream& operator<<(std::wostream& os, const SString& s)
{
    os << s.Str;
    return os;
}

/**
 * @brief Stream extraction operator for wide input streams (reads an entire line).
 *
 * @param[in,out] is Wide input stream object.
 * @param[out] s Target `SString` instance to receive the input line.
 * @return std::wistream& Reference to the stream (`is`).
 *
 * @remarks Reads up to the newline character using `std::getline`.
 */
std::wistream& operator>>(std::wistream& is, SString& s) {
    std::wstring temp;
    std::getline(is, temp);   // read entire line including spaces

    s = temp.c_str();         // assign into SString (uses operator=(const wchar_t*))
    return is;
}

// ---------------- UTF-8/UTF-16 Conversion ----------------

/**
 * @brief Static factory method that creates an `SString` from a UTF-8 encoded string.
 *
 * @param[in] utf8 Pointer to a null-terminated UTF-8 narrow string.
 * @return SString Constructed `SString` containing wide characters.
 *
 * @remarks Utilizes Windows API (`MultiByteToWideChar`) or POSIX `iconv`.
 */
SString SString::FromUtf8(const char* utf8) {
#ifdef _WIN32
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0);
    std::wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, &ws[0], len);
    return SString(ws.c_str());
#else
    iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
    if (cd == (iconv_t)-1) return SString(L"");

    size_t inBytes = std::strlen(utf8);
    size_t outBytes = (inBytes + 1) * sizeof(wchar_t);
    std::wstring ws;
    ws.resize(inBytes + 1);

    char* inBuf = const_cast<char*>(utf8);
    char* outBuf = reinterpret_cast<char*>(&ws[0]);
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    return SString(ws.c_str());
#endif
}

/**
 * @brief Converts the wide string contents into a standard UTF-8 encoded `std::string`.
 *
 * @return std::string Standard string encoded in UTF-8.
 *
 * @remarks Useful for exporting system-native wide strings to network or file pipelines requiring UTF-8 encoding.
 */
std::string SString::ToUtf8() const {
#ifdef _WIN32
    int len = WideCharToMultiByte(CP_UTF8, 0, Str, -1, nullptr, 0, nullptr, nullptr);
    std::string s(len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, Str, -1, &s[0], len, nullptr, nullptr);
    return s;
#else
    iconv_t cd = iconv_open("UTF-8", "WCHAR_T");
    if (cd == (iconv_t)-1) return "";

    size_t inBytes = (std::wcslen(Str) + 1) * sizeof(wchar_t);
    size_t outBytes = inBytes * 4; // worst case
    std::string s;
    s.resize(outBytes);

    char* inBuf = reinterpret_cast<char*>(Str);
    char* outBuf = &s[0];
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    s.resize(std::strlen(s.c_str())); // trim
    return s;
#endif
}