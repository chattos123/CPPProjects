/*
 * File: sStringTester.cpp
 * Author: Soumyajit C
 * Description: Implements the SString-related tester methods for the application.
 */

#include "sStringTester.h"
#include <cstring>
#include <cassert>
#include <cmath>       // for std::abs
#include <algorithm>   // for std::find

#if defined(_WIN32) || defined(__CYGWIN__)
    #include <fcntl.h>
    #include <io.h>
    #include <windows.h>
#endif

/**
 * @brief Tests construction and initialization behavior of SString.
 * @remark This method prints the test output to the console for inspection.
 * @return void
 */
void sStringTester::TestConstruction() 
{
    std::wcout << L"\n*** Construction Test start ***\n";
    SString s1(L"Hello Wide");
    SString s2("Hello Narrow");
    SString s3 = SString::Empty();
    bool bTest = SString::IsEmpty(s3);

    std::cout << (bTest ? "String is Empty\n" : "String is not Empty\n");
    std::wcout << L"Constructed s1: " << s1 << std::endl;
    std::wcout << L"Constructed s2: " << s2 << std::endl;
    std::wcout << L"Empty string s3 length: " << s3.length() << std::endl;
    std::wcout << L"*** Construction Test end ***\n\n";
}

/**
 * @brief Tests assignment operations for SString.
 * @remark This method validates wide, narrow, and object-based assignment paths.
 * @return void
 */
void sStringTester::TestAssignment() 
{
    std::wcout << L"\n*** Assignment Test start ***\n";
    SString s1(L"Hello Wide");
    SString s3;
    s3 = L"Assigned Wide";
    std::wcout << L"s3 after wchar_t* assignment: " << s3 << std::endl;
    s3 = "Assigned Narrow";
    std::wcout << L"s3 after char* assignment: " << s3 << std::endl;
    s3 = s1;
    std::wcout << L"s3 after SString assignment: " << s3 << std::endl;
    std::wcout << L"*** Assignment Test end ***\n\n";
}

/**
 * @brief Tests concatenation behavior for SString.
 * @remark This method confirms string concatenation with string and C-string operands.
 * @return void
 */
void sStringTester::TestConcatenation() 
{
    std::wcout << L"\n*** Concatenation Test start ***\n";
    SString s1(L"Hello Wide");
    SString s2("Hello Narrow");
    std::wcout << L"SString + SString: " << (s1 + s2) << std::endl;
    std::wcout << L"SString + wchar_t*: " << (s1 + L" Extra") << std::endl;
    std::wcout << L"SString + char*: " << (s1 + " Narrow Extra") << std::endl;
    std::wcout << L"*** Concatenation Test end ***\n\n";
}

/**
 * @brief Tests append operations for SString.
 * @remark This method exercises the compound append operator with different input types.
 * @return void
 */
void sStringTester::TestAppend() 
{
    std::wcout << L"\n*** Append Test start ***\n";
    SString s1(L"Hello Wide");
    SString s2("Hello Narrow");
    s1 += L" Appended Wide";
    s1 += " Appended Narrow";
    s1 += s2;
    std::wcout << L"After appends: " << s1 << std::endl;
    std::wcout << L"*** Append Test end ***\n\n";
}

/**
 * @brief Tests case conversion helpers of SString.
 * @remark This method validates uppercase, lowercase, and toggle-case operations.
 * @return void
 */
void sStringTester::TestCaseConversions() 
{
    std::wcout << L"\n*** Case Conversion Test start ***\n";
    SString s2("Hello Narrow");
    std::wcout << L"Uppercase: " << s2.to_upper() << std::endl;
    std::wcout << L"Lowercase: " << s2.to_lower() << std::endl;
    std::wcout << L"Toggle case: " << s2.change_case() << std::endl;
    std::wcout << L"*** Case Conversion Test end ***\n\n";
}

/**
 * @brief Tests reverse operations for SString.
 * @remark This method verifies the reversal logic for string content.
 * @return void
 */
void sStringTester::TestReverse() 
{
    std::wcout << L"\n*** Reverse Test start ***\n";
    SString s2("Hello Narrow");
    std::wcout << L"Reversed: " << s2.revert() << std::endl;
    std::wcout << L"*** Reverse Test end ***\n\n";
}

/**
 * @brief Tests substring extraction behavior.
 * @remark This method validates substring creation from a given range.
 * @return void
 */
void sStringTester::TestSubstring() 
{
    std::wcout << L"\n*** Substring Test start ***\n";
    SString s2("Hello Narrow");
    std::wcout << L"Substring (0,5): " << s2.substring(0, 5) << std::endl;
    std::wcout << L"*** Substring Test end ***\n\n";
}

/**
 * @brief Tests indexing and character access behavior.
 * @remark This method verifies both read and write access through the index operator.
 * @return void
 */
void sStringTester::TestIndexing() 
{
    std::wcout << L"\n*** Indexing Test start ***\n";
    SString s2("Hello Narrow");
    wchar_t ch = s2[1];
    std::wcout << L"Character at index 1: " << ch << std::endl;
    s2[0] = L'J';
    std::wcout << L"After replacing index 0: " << s2 << std::endl;
    std::wcout << L"*** Indexing Test end ***\n\n";
}

/**
 * @brief Tests comparison operations for SString.
 * @remark This method validates matching logic using the string comparison helper.
 * @return void
 */
void sStringTester::TestComparison() 
{
    std::wcout << L"\n*** Comparison Test start ***\n";
    SString s2("Jello Narrow");
    bool match = s2.match_string(L"Jello Narrow");
    std::wcout << L"Comparison result: " << (match ? L"true" : L"false") << std::endl;
    std::wcout << L"*** Comparison Test end ***\n\n";
}

/**
 * @brief Tests clearing the contents of SString.
 * @remark This method confirms that the string becomes empty after clearing.
 * @return void
 */
void sStringTester::TestClear() 
{
    std::wcout << L"\n*** Clear Test start ***\n";
    SString s2("Hello Narrow");
    s2.Clear();
    std::wcout << L"After Clear(): '" << s2 << L"' length=" << s2.length() << std::endl;
    std::wcout << L"*** Clear Test end ***\n\n";
}

/**
 * @brief Tests conversion helpers for SString.
 * @remark This method checks conversions to wide string, UTF-8, and C-string formats.
 * @return void
 */
void sStringTester::TestConversions() 
{
    std::wcout << L"\n*** Conversion Test start ***\n";
    SString s1(L"Hello Wide");
    std::wstring ws = s1.ToString();
    std::wcout << L"ToString() -> std::wstring: " << ws << std::endl;
    std::string utf8 = s1.ToUtf8();
    std::cout << "ToUtf8() -> std::string: " << utf8 << std::endl;
    std::cout << "c_charString() -> const char*: " << s1.c_charString() << std::endl;
    std::wcout << L"*** Conversion Test end ***\n\n";
}

/**
 * @brief Tests user input handling for SString.
 * @remark This method reads a line from standard input and stores it in the string.
 * @return void
 */
void sStringTester::TestInput() 
{
    std::wcout << L"\n*** Input Test start ***\n";
#if defined(_WIN32)
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif

    SString sIN;
    std::wcout << L"Enter a full line: ";
    std::wstring temp;
    std::getline(std::wcin, temp);
    sIN = temp.c_str();
    std::wcout << L"You entered (wide): " << sIN << std::endl;
    std::cout << "You entered (UTF-8): " << sIN.c_charString() << std::endl;

    std::wcout << L"*** Input Test end ***\n\n";
#if defined(_WIN32)
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
#endif
}

/**
 * @brief Tests tokenization behavior of SString.
 * @remark This method validates default and custom delimiter splitting.
 * @return void
 */
void sStringTester::TestTokenize()
{
    std::wcout << L"\n*** Tokenize Test start ***\n";
    SString sToken(L"Hello, world! This is a tokenizer test.");
    auto tokens = sToken.Tokenize();
    std::wcout << L"Tokens:" << std::endl;
    for (const auto& t : tokens) std::wcout << L"- " << t << std::endl;
    auto tokens2 = sToken.Tokenize(L" ,");
    std::wcout << L"\nTokens with custom delimiters:" << std::endl;
    for (const auto& t : tokens2) std::wcout << L"- " << t << std::endl;
    std::wcout << L"*** Tokenize Test end ***\n\n";
}

/**
 * @brief Tests iterator support for SString.
 * @remark This method verifies range-based iteration and character lookup through iterators.
 * @return void
 */
void sStringTester::TestIterator() 
{
    std::cout << "\n*** Iterator Test start ***\n";
    SString s(L"Programming is মজার when you solve problems quickly!");
    for (wchar_t ch : s) std::wcout << ch << ' ';
    std::wcout << std::endl;
    auto it = std::find(s.begin(), s.end(), L'W');
    if (it != s.end()) std::wcout << L"Found character: " << *it << std::endl;
    std::cout << "*** Iterator Test end ***\n\n";
}

/**
 * @brief Tests implicit and explicit cast operators of SString.
 * @remark This method validates conversions to wide strings, narrow strings, and numeric types.
 * @return void
 */
void sStringTester::TestCastOpearator()
{
    std::cout << "[RUNNING] TestCastOperator()...\n";

    // 1. Test Wide C-String Casting (const wchar_t*)
    {
        SString s(L"Hello Wide World");
        const wchar_t* rawWide = static_cast<const wchar_t*>(s); // Explicit cast works!
        assert(rawWide != nullptr);
        assert(std::wcscmp(rawWide, L"Hello Wide World") == 0);
    }

    // 2. Test Narrow UTF-8 C-String Casting (const char*)
    {
        SString s("Hello Narrow World"); // Pass narrow string to constructor
        const char* rawNarrow = static_cast<const char*>(s);
        assert(rawNarrow != nullptr);
        assert(std::strcmp(rawNarrow, "Hello Narrow World") == 0);
    }
    // 3. Test std::wstring Casting
    {
        SString s(L"Testing wstring");
        std::wstring ws = static_cast<std::wstring>(s); // Invokes operator std::wstring() cleanly!
        assert(ws == L"Testing wstring");
    }

    // 4. Test std::string (UTF-8) Casting
    {
        SString s(L"Testing string");
        std::string str = static_cast<std::string>(s); // Invokes operator std::string() cleanly!
        assert(str == "Testing string");
    }

    // 5. Test Integer Casting (int)
    {
        SString s1(L"42");
        SString s2(L"-1024");
        
        int val1 = static_cast<int>(s1);
        int val2 = static_cast<int>(s2);
        
        assert(val1 == 42);
        assert(val2 == -1024);

        // Test exception on invalid integer
        bool caught = false;
        try {
            SString sInvalid(L"NotANumber");
            int valInvalid = static_cast<int>(sInvalid);
            (void)valInvalid;
        } catch (const std::invalid_argument&) {
            caught = true;
        }
        assert(caught);
    }

    // 6. Test Double Casting (double)
    {
        SString s1(L"3.14159");
        SString s2(L"-0.005");

        double val1 = static_cast<double>(s1);
        double val2 = static_cast<double>(s2);

        assert(std::abs(val1 - 3.14159) < 1e-5);
        assert(std::abs(val2 - (-0.005)) < 1e-5);

        // Test exception on invalid double
        bool caught = false;
        try {
            SString sInvalid(L"InvalidDouble");
            double valInvalid = static_cast<double>(sInvalid);
            (void)valInvalid;
        } catch (const std::invalid_argument&) {
            caught = true;
        }
        assert(caught);
    }

    std::cout << "[SUCCESS] TestCastOperator() passed all assertions!\n";
}

/**
 * @brief Tests Unicode text handling for SString.
 * @remark This method validates Unicode output, tokenization, and iteration behavior.
 * @return void
 */
void sStringTester::TestUnicodeText() 
{
#if defined(_WIN32)
    // 1. Set Windows Console Code Page to UTF-8
    UINT oldOutputCP = GetConsoleOutputCP();
    UINT oldCP = GetConsoleCP();
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::wcout << L"\n*** UnicodeText Test start ***\n";

    // Example with Bengali + Emoji
    SString s1(L"বাংলা লেখা 😊");
    std::wcout << L"Original Unicode string: " << s1 << std::endl;

    // Append more Unicode (Japanese)
    s1 += L" —追加テキスト";
    std::wcout << L"After append: " << s1 << std::endl;

    // Tokenize Unicode text
    auto tokens = s1.Tokenize();
    std::wcout << L"Tokens:" << std::endl;
    for (const auto& t : tokens) {
        std::wcout << L"- " << t << std::endl;
    }

    // Iterate over characters
    std::wcout << L"Iterating characters:" << std::endl;
    for (wchar_t ch : s1) {
        std::wcout << ch << L' ';
    }
    std::wcout << std::endl;

    // Conversion checks
    std::wstring ws = s1.ToString();
    std::wcout << L"ToString() -> std::wstring: " << ws << std::endl;

    // Flush wide stream before writing to narrow stream
    std::fflush(stdout);

    std::string utf8 = s1.ToUtf8();
    std::cout << "ToUtf8() -> std::string: " << utf8 << std::endl;

    std::wcout << L"*** UnicodeText Test end ***\n\n";

#if defined(_WIN32)
    // Restore original console code pages
    SetConsoleOutputCP(oldOutputCP);
    SetConsoleCP(oldCP);
#endif
}

/**
 * @brief Executes all SString-related tests.
 * @remark This method runs the full test suite in a defined order and prints the results.
 * @return void
 */
void sStringTester::RunAllTests() 
{
    std::cout << "\n==============================\n";
    std::cout << "Running all SString tests...\n";
    std::cout << "==============================\n";

    TestConstruction();
    TestAssignment();
    TestConcatenation();
    TestAppend();
    TestCaseConversions();
    TestReverse();
    TestSubstring();
    TestIndexing();
    TestComparison();
    TestClear();
    TestCastOpearator();
    TestConversions();
    TestUnicodeText();
    TestTokenize();
    TestIterator();
    // TestInput(); // optional, requires user input
    std::cout << "\n==============================\n";
    std::cout << "all SString tests Passed...\n";
    std::cout << "==============================\n";
}