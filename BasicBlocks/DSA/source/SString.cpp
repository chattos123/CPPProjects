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
 * @brief Allocates memory and copies the given wide string safely.
 * @param s Input wide string to copy.
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
 * @brief Safely copies a wide string into a destination buffer.
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
 * @brief Safely concatenates a wide string onto a destination buffer.
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

SString::SString() : Str(new wchar_t[1]), str_len(0)
{
    Str[0] = L'\0';
}

SString::SString(const wchar_t* s)
{
    allocate_and_copy(s);
}

// ---------------- Constructor from char* ----------------

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

    size_t inBytes = std::strlen(s);
    size_t outBytes = (inBytes + 1) * sizeof(wchar_t);
    std::wstring ws;
    ws.resize(inBytes + 1);

    char* inBuf = const_cast<char*>(s);
    char* outBuf = reinterpret_cast<char*>(&ws[0]);
    iconv(cd, &inBuf, &inBytes, &outBuf, &outBytes);
    iconv_close(cd);

    str_len = std::wcslen(ws.c_str());
    Str = new wchar_t[str_len + 1];
    safe_copy(Str, ws.c_str(), str_len + 1);
#endif
}

SString::SString(const SString& other) {
    allocate_and_copy(other.Str);
}

// ---------------- Assignment ----------------

SString& SString::operator=(const SString& other) 
{
    if (this != &other)
    {
        delete[] Str;
        allocate_and_copy(other.Str);
    }

    return *this;
}

SString& SString::operator=(const wchar_t* s) {
    delete[] Str;
    allocate_and_copy(s);
    return *this;
}

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

SString::~SString() {
    delete[] Str;
    Str = nullptr;
}

// ---------------- Accessors ----------------

int SString::length() const { return str_len; }

const wchar_t* SString::c_str() const { return Str; }

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

SString SString::Empty() { return SString(); }

void SString::Clear() {
    delete[] Str;          // free old buffer
    Str = new wchar_t[1];  // allocate new buffer with just null terminator
    Str[0] = L'\0';
    str_len = 0;
}


std::wstring SString::ToString() const {
    return std::wstring(Str, str_len);
}


//subsstring
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

SString SString::to_upper() const
{
    SString result(*this);
    for (int i = 0; i < result.str_len; i++)
        result.Str[i] = std::towupper(result.Str[i]);
    return result;
}

SString SString::to_lower() const
{
    SString result(*this);
    for (int i = 0; i < result.str_len; i++)
        result.Str[i] = std::towlower(result.Str[i]);
    return result;
}

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

SString SString::revert() const 
{
    SString result(*this);
    for (int i = 0; i < result.str_len / 2; i++)
        std::swap(result.Str[i], result.Str[result.str_len - i - 1]);
    return result;
}

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

// Helper: convert narrow delimiters to wide string
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

std::vector<SString> SString::Tokenize(const std::string delimiters) const 
{
    return Tokenize(delimiters.c_str());
}

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

bool SString::match_string(const wchar_t* s) const 
{
    return std::wcscmp(Str, s) == 0;
}

//statics

bool SString::IsEmpty(const SString& s) {
    return s.str_len == 0;
}

bool SString::IsNull(const SString& s) {
    return s.Str == nullptr;
}

bool SString::IsNullOrEmpty(const SString& s) {
    return (s.Str == nullptr) || (s.str_len == 0);
}


// ---------------- Concatenation ----------------

SString SString::operator+(const SString& other) const
{
    wchar_t* buffer = new wchar_t[str_len + other.str_len + 1];
    safe_copy(buffer, Str, str_len + other.str_len + 1);
    safe_concat(buffer, other.Str, str_len + other.str_len + 1);
    SString result(buffer);
    delete[] buffer;
    return result;
}

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

// Read-only access
const wchar_t& SString::operator[](int index) const {
    if (index < 0 || index >= str_len) {
        throw std::out_of_range("SString index out of range");
    }
    return Str[index];
}

// Writable access
wchar_t& SString::operator[](int index) {
    if (index < 0 || index >= str_len) {
        throw std::out_of_range("SString index out of range");
    }
    return Str[index];
}



// ---------------- Stream Operators ----------------

std::wostream& operator<<(std::wostream& os, const SString& s)
{
    os << s.Str;
    return os;
}

/* std::wistream& operator>>(std::wistream& is, SString& s)
{
    wchar_t temp[1024];
    is.getline(temp, 1024); // read a token (whitespace-delimited)
    s = temp;   // assign into SString (uses your operator=(const wchar_t*)
    return is;
} */

// Input stream operator: read full line
std::wistream& operator>>(std::wistream& is, SString& s) {
    std::wstring temp;
    std::getline(is, temp);   // read entire line including spaces

    s = temp.c_str();         // assign into SString (uses operator=(const wchar_t*))
    return is;
}

// ---------------- UTF-8/UTF-16 Conversion ----------------

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
