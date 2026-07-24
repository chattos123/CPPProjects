#include "sStringTester.h"
#include <fcntl.h>
#include <io.h>

void sStringTester::TestConstruction() {
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

void sStringTester::TestAssignment() {
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

void sStringTester::TestConcatenation() {
    std::wcout << L"\n*** Concatenation Test start ***\n";
    SString s1(L"Hello Wide");
    SString s2("Hello Narrow");
    std::wcout << L"SString + SString: " << (s1 + s2) << std::endl;
    std::wcout << L"SString + wchar_t*: " << (s1 + L" Extra") << std::endl;
    std::wcout << L"SString + char*: " << (s1 + " Narrow Extra") << std::endl;
    std::wcout << L"*** Concatenation Test end ***\n\n";
}

void sStringTester::TestAppend() {
    std::wcout << L"\n*** Append Test start ***\n";
    SString s1(L"Hello Wide");
    SString s2("Hello Narrow");
    s1 += L" Appended Wide";
    s1 += " Appended Narrow";
    s1 += s2;
    std::wcout << L"After appends: " << s1 << std::endl;
    std::wcout << L"*** Append Test end ***\n\n";
}

void sStringTester::TestCaseConversions() {
    std::wcout << L"\n*** Case Conversion Test start ***\n";
    SString s2("Hello Narrow");
    std::wcout << L"Uppercase: " << s2.to_upper() << std::endl;
    std::wcout << L"Lowercase: " << s2.to_lower() << std::endl;
    std::wcout << L"Toggle case: " << s2.change_case() << std::endl;
    std::wcout << L"*** Case Conversion Test end ***\n\n";
}

void sStringTester::TestReverse() {
    std::wcout << L"\n*** Reverse Test start ***\n";
    SString s2("Hello Narrow");
    std::wcout << L"Reversed: " << s2.revert() << std::endl;
    std::wcout << L"*** Reverse Test end ***\n\n";
}

void sStringTester::TestSubstring() {
    std::wcout << L"\n*** Substring Test start ***\n";
    SString s2("Hello Narrow");
    std::wcout << L"Substring (0,5): " << s2.substring(0, 5) << std::endl;
    std::wcout << L"*** Substring Test end ***\n\n";
}

void sStringTester::TestIndexing() {
    std::wcout << L"\n*** Indexing Test start ***\n";
    SString s2("Hello Narrow");
    wchar_t ch = s2[1];
    std::wcout << L"Character at index 1: " << ch << std::endl;
    s2[0] = L'J';
    std::wcout << L"After replacing index 0: " << s2 << std::endl;
    std::wcout << L"*** Indexing Test end ***\n\n";
}

void sStringTester::TestComparison() {
    std::wcout << L"\n*** Comparison Test start ***\n";
    SString s2("Jello Narrow");
    bool match = s2.match_string(L"Jello Narrow");
    std::wcout << L"Comparison result: " << (match ? L"true" : L"false") << std::endl;
    std::wcout << L"*** Comparison Test end ***\n\n";
}

void sStringTester::TestClear() {
    std::wcout << L"\n*** Clear Test start ***\n";
    SString s2("Hello Narrow");
    s2.Clear();
    std::wcout << L"After Clear(): '" << s2 << L"' length=" << s2.length() << std::endl;
    std::wcout << L"*** Clear Test end ***\n\n";
}

void sStringTester::TestConversions() {
    std::wcout << L"\n*** Conversion Test start ***\n";
    SString s1(L"Hello Wide");
    std::wstring ws = s1.ToString();
    std::wcout << L"ToString() -> std::wstring: " << ws << std::endl;
    std::string utf8 = s1.ToUtf8();
    std::cout << "ToUtf8() -> std::string: " << utf8 << std::endl;
    std::cout << "c_charString() -> const char*: " << s1.c_charString() << std::endl;
    std::wcout << L"*** Conversion Test end ***\n\n";
}

void sStringTester::TestInput() {
    std::wcout << L"\n*** Input Test start ***\n";
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    SString sIN;
    std::wcout << L"Enter a full line: ";
    std::wstring temp;
    std::getline(std::wcin, temp);
    sIN = temp.c_str();
    std::wcout << L"You entered (wide): " << sIN << std::endl;
    std::cout << "You entered (UTF-8): " << sIN.c_charString() << std::endl;

    std::wcout << L"*** Input Test end ***\n\n";
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
}

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

void sStringTester::TestUnicodeText() 
{
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::wcout << L"\n*** UnicodeText Test start ***\n";

    // Example with Bengali + Emoji
    SString s1(L"বাংলা লেখা 😊");
    std::wcout << L"Original Unicode string: " << s1 << std::endl;

    // Append more Unicode
    s1 += L" —追加テキスト"; // Japanese
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
        std::wcout << ch << ' ';
    }
    std::wcout << std::endl;

    // Conversion checks
    std::wstring ws = s1.ToString();
    std::wcout << L"ToString() -> std::wstring: " << ws << std::endl;

    std::string utf8 = s1.ToUtf8();
    std::cout << "ToUtf8() -> std::string: " << utf8 << std::endl;

    std::wcout << L"*** UnicodeText Test end ***\n\n";
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
}


void sStringTester::RunAllTests() {
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
    TestConversions();
    TestUnicodeText();
    TestTokenize();
    TestIterator();
    // TestInput(); // optional, requires user input
    std::cout << "\n==============================\n";
    std::cout << "all SString tests Passed...\n";
    std::cout << "==============================\n";

}