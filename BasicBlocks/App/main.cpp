#include <iostream>
#include <string>
#include <algorithm>
#include <fcntl.h>
#include <io.h>
#include "SMathLib.h"
#include "SCalculator.h"
#include "SComplex.h"
#include "SStack.h"
#include "SList.h"
#include "SListT.h"
#include "SVector.h"
#include "SVectorT.h"
#include "SStackT.h"
#include "SListStackT.h"
#include "SQueue.h"
#include "SQueueT.h"
#include "SString.h"
#include "SPair.h"
#include "STuple.h"
#include "STupleGet.h"

// Testing app

void TestCalculator();
void TestStack();
void TestStackT();
void TestListT();
void TestVector();
void TestVectorT();
void TestQueue();
void TestQueueT(); 
void TestComplex();
void TestString();
void TestStringIteratyor();
void TestSPair();
void TestTuple();

int main() {

        std::cout << "Calculator App Version: ";
    #ifdef PROJECT_VERSION
        std::cout << PROJECT_VERSION;
    #else
        std::cout << "unknown";
    #endif
        std::cout << std::endl;

    // You can also use it in conditional compilation:
#if defined(PROJECT_VERSION)
    std::cout << "Build stamped with version info." << std::endl;
#else
    std::cout << "No version info available." << std::endl;
#endif
    std::cout << "Calling DLL function..." << std::endl;
    helloFromDLL();

    //Test calculator
    TestCalculator();

    //Test complex
    TestComplex();

    //Test stack
    TestStack();

    //Test stack T
    TestStackT();

    //Test list T
    TestListT();

    //Test vector
    TestVector();

    //Test vector T
    TestVectorT();

    // TestQueue
    TestQueue();

    // TestQueueT
    TestQueueT();

    //TestPair
    TestSPair();

    //Test Tuple
    TestTuple();

    //TestString

    // Force console to wide mode
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    TestStringIteratyor();

    TestString();

    return 0;
}

void TestCalculator()
{
    std::cout << "Testing SCalculator...\n";
    SCalculator calc;

    double a = 10.0, b = 5.0;

    std::cout << "Add: " << calc.add(a, b) << "\n";
    std::cout << "Subtract: " << calc.subtract(a, b) << "\n";
    std::cout << "Multiply: " << calc.multiply(a, b) << "\n";
    std::cout << "Divide: " << calc.divide(a, b) << "\n";
    std::cout << "Modulo: " << calc.mod(a, b) << "\n";

    std::cout << "SCalculator tests completed.\n";
}

/*void TestComplex()
{
    std::cout << "Testing SComplex...\n";

    SComplex C1(3.0, 4.0);
    SComplex C2(1.0, -2.0);
    std::cout << "C1: ";
    C1.display();
    std::cout << "C2: ";
    C2.display();

    SComplex sum = C1 + C2;
    sum.display();

    SComplex prod = C1 * C2;
    prod.display();

    //SComplex scaled = C1 * 2;
    //scaled.display();

    C1.display();

    std::cout << "SComplex tests completed.\n";
}*/

void TestComplex()
{
    std::cout << "Testing Complex class...\n";

    // Create some complex numbers
    SComplex c1(3.0, 4.0);   // 3 + 4i
    SComplex c2(1.0, 2.0);   // 1 + 2i

    // Display them
    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";

    // Addition
    SComplex sum = c1 + c2;
    std::cout << "c1 + c2 = " << sum << "\n";

    // Subtraction
    SComplex diff = c1 - c2;
    std::cout << "c1 - c2 = " << diff << "\n";

    // Multiplication
    SComplex prod = c1 * c2;
    std::cout << "c1 * c2 = " << prod << "\n";

    // Division
    SComplex quot = c1 / c2;
    std::cout << "c1 / c2 = " << quot << "\n";

    // Magnitude
    //std::cout << "|c1| = " << c1.magnitude() << "\n";

    // Equality check
    //std::cout << "c1 == c2 ? " << (c1 == c2 ? "true" : "false") << "\n";

    std::cout << "Complex class tests completed.\n";
}



void TestStack()
{
    std::cout << "Testing SStack...\n";
    SStack stack;
    stack.push(10); 
    stack.push(20);
    std::cout << "Top element: " << stack.top() << "\n";
    stack.pop();
    std::cout << "Top element after pop: " << stack.top() << "\n";
    std::cout << "SStack tests completed.\n";
}

void TestStackT()
{
    std::cout << "Testing SStackT...\n";
    SStackT<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    std::cout << "Top element: " << intStack.top() << "\n";
    intStack.display();
    intStack.pop();
    std::cout << "Top element after pop: " << intStack.top() << "\n";
    intStack.display();

    SStackT<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "Top element: " << stringStack.top() << "\n";
    stringStack.display();
    stringStack.pop();
    std::cout << "Top element after pop: " << stringStack.top() << "\n";
    stringStack.display();

    std::cout << "SStackT tests completed.\n";
}

void TestListStack()
{
    std::cout << "Testing SListStackT...\n";
    SListStackT<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    std::cout << "Top element: " << intStack.top() << "\n";
    intStack.display();
    intStack.pop();
    std::cout << "Top element after pop: " << intStack.top() << "\n";
    intStack.display();

    SListStackT<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "Top element: " << stringStack.top() << "\n";
    stringStack.display();
    stringStack.pop();
    std::cout << "Top element after pop: " << stringStack.top() << "\n";
    stringStack.display();
    std::cout << "SListStackT tests completed.\n";
}

void TestList()
{
    std::cout << "Testing SList...\n";
    SList list;
    list.AddElement(5);
    list.AddElement(10);
    list.AddElement(15);
    list.Display();
    list.AddElementAfter(1, 12); // Add 12 after the second element
    list.Display();
    list.DeleteElement(); // Delete the last element
    list.Display();
    std::cout << "SList tests completed.\n";
}

void TestListT()
{
    std::cout << "Testing SListT...\n";
    //list T
    SListT<int> intList;
    intList.AddElement(10);
    intList.AddElement(20);
    intList.AddElement(30);
    intList.Display();

    SListT<std::string> stringList;
    stringList.AddElement("Hello");
    stringList.AddElement("World");
    stringList.Display();
    std::cout << "SListT tests completed.\n";
}

void TestVector()
 {
    std::cout << "Testing SVector...\n";
    SVector vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.display(); // Output: [ 10 20 30 ]

    std::cout << "Element at index 1: " << vec.at(1) << "\n";

    vec.pop_back();
    vec.display(); // Output: [ 10 20 ]

    vec[0] = 100; // Using operator[] to modify the first element
    vec.display(); // Output: [ 100 20 ]

     // Read using []
    int p = vec[1];   // x = 10
    std::cout << "x = " << p << "\n";

    SVector v1;
    v1.push_back(1);
    v1.push_back(2);

    SVector v2;
    v2.push_back(3);
    v2.push_back(4);

    // Copy constructor
    SVector v3(v1);
    v3.display(); // [ 1 2 ]

    // Assignment operator
    SVector v4;
    v4 = v2;
    v4.display(); // [ 3 4 ]

    // Addition operator
    SVector v5 = v1 + v2;
    v5.display(); // [ 1 2 3 4 ]

    std::cout << "SVector tests completed.\n";
 }

 void TestVectorT()
 {
    std::cout << "Testing SVectorT...\n";
    SVectorT<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    vec.display(); // Output: [ 10 20 30 ]

    std::cout << "Element at index 1: " << vec.at(1) << "\n";

    vec.pop_back();
    vec.display(); // Output: [ 10 20 ]

    vec[0] = 100; // Using operator[] to modify the first element
    vec.display(); // Output: [ 100 20 ]

     // Read using []
    int x = vec[1];   // x = 10
    std::cout << "x = " << x << "\n";

    SVectorT<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    SVectorT<int> v2;
    v2.push_back(3);
    v2.push_back(4);

    // Copy constructor
    SVectorT<int> v3(v1);
    v3.display(); // [ 1 2 ]

    // Assignment operator
    SVectorT<int> v4;
    v4 = v2;
    v4.display(); // [ 3 4 ]

    // Addition operator
    SVectorT<int> v5 = v1 + v2;
    v5.display(); // [ 1 2 3 4 ]

    //Test iterators
    std::cout << "Iterating over v5 using iterators:\n";
    for (auto it = v5.begin(); it != v5.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "SVectorT tests completed.\n";
 }

 void TestQueue()
 {
    std::cout << "Testing SQueue...\n";
    SQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Front element: " << queue.front() << "\n"; // Output: 10
    std::cout << "Dequeue: " << queue.dequeue() << "\n"; // Output: 10
    std::cout << "Front element after dequeue: " << queue.front() << "\n"; // Output: 20

    std::cout << "SQueue tests completed.\n";
 }

 void TestQueueT()
 {
    std::cout << "Testing SQueueT...\n";
    SQueueT<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Front element: " << queue.front() << "\n"; // Output: 10
    std::cout << "Dequeue: " << queue.dequeue() << "\n"; // Output: 10
    std::cout << "Front element after dequeue: " << queue.front() << "\n"; // Output: 20

    SQueueT<std::string> strQueue;
    strQueue.enqueue("Hello");
    strQueue.enqueue("World");
    strQueue.enqueue("!");

    std::cout << "Front element: " << strQueue.front() << "\n"; // Output: Hello
    std::cout << "Dequeue: " << strQueue.dequeue() << "\n"; // Output: Hello
    std::cout << "Front element after dequeue: " << strQueue.front() << "\n"; // Output: World

    std::cout << "SQueueT tests completed.\n";
 }

 void TestString() {
    std::wcout << L"--- SString Feature Test ---" << std::endl;

    // 1. Construction
    SString s1(L"Hello Wide");
    SString s2("Hello Narrow");
    SString s3 = SString::Empty();
    bool bTest = SString::IsEmpty(s3);

    if(bTest)
    {
        std::cout << "String is Empty";
    }
    else
    {
        std::cout << "String is  not Empty";   
    }

    std::wcout << L"Constructed s1: " << s1 << std::endl;
    std::wcout << L"Constructed s2: " << s2 << std::endl;
    std::wcout << L"Empty string s3 length: " << s3.length() << std::endl;

    // 2. Assignment
    s3 = L"Assigned Wide";
    std::wcout << L"s3 after wchar_t* assignment: " << s3 << std::endl;
    s3 = "Assigned Narrow";
    std::wcout << L"s3 after char* assignment: " << s3 << std::endl;
    s3 = s1;
    std::wcout << L"s3 after SString assignment: " << s3 << std::endl;

    // 3. Concatenation
    SString concat1 = s1 + s2;
    std::wcout << L"Concatenation (SString + SString): " << concat1 << std::endl;
    SString concat2 = s1 + L" Extra";
    std::wcout << L"Concatenation (SString + wchar_t*): " << concat2 << std::endl;
    SString concat3 = s1 + " Narrow Extra";
    std::wcout << L"Concatenation (SString + char*): " << concat3 << std::endl;

    // 4. Append operators
    s1 += L" Appended Wide";
    std::wcout << L"s1 after += wchar_t*: " << s1 << std::endl;
    s1 += " Appended Narrow";
    std::wcout << L"s1 after += char*: " << s1 << std::endl;
    s1 += s2;
    std::wcout << L"s1 after += SString: " << s1 << std::endl;

    // 5. Case conversions
    std::wcout << L"Uppercase: " << s2.to_upper() << std::endl;
    std::wcout << L"Lowercase: " << s2.to_lower() << std::endl;
    std::wcout << L"Toggle case: " << s2.change_case() << std::endl;

    // 6. Reverse
    std::wcout << L"Reversed: " << s2.revert() << std::endl;

    // 7. Substring
    SString sub = s2.substring(0, 5);
    std::wcout << L"Substring (0,5): " << sub << std::endl;

    // 8. Indexing
    wchar_t ch = s2[1];
    std::wcout << L"Character at index 1: " << ch << std::endl;
    s2[0] = L'J';
    std::wcout << L"s2 after replacing index 0 with 'J': " << s2 << std::endl;

    // 9. Comparison
    bool match = s2.match_string(L"Jello Narrow");
    std::wcout << L"Comparison with 'Jello Narrow': " << (match ? L"true" : L"false") << std::endl;

    // 10. Clear
    s2.Clear();
    std::wcout << L"s2 after Clear(): '" << s2 << L"' length=" << s2.length() << std::endl;

    // 11. Conversions
    std::wstring ws = s1.ToString();
    std::wcout << L"ToString() -> std::wstring: " << ws << std::endl;

    std::string utf8 = s1.ToUtf8();
    std::cout << "ToUtf8() -> std::string: " << utf8 << std::endl;

    const char* cstr = s1.c_charString();
    std::cout << "c_charString() -> const char*: " << cstr << std::endl;

    std::wcout << L"--- End of Test ---" << std::endl;

    // cin
    SString sIN;
    std::wcout << L"Enter a full line: ";

    std::wstring temp;
    std::getline(std::wcin, temp);
    sIN = temp.c_str();

    std::wcout << L"You entered (wide): " << sIN << std::endl;
    std::cout << "You entered (UTF-8): " << sIN.c_charString() << std::endl;

    // tokenize test
    SString sToken(L"Hello, world! This is a tokenizer test.");

    // Default delimiters: space, tab, newline
    auto tokens = sToken.Tokenize();

    std::wcout << L"Tokens:" << std::endl;
    for (const auto& t : tokens) {
        std::wcout << L"- " << t << std::endl;
    }

    // Custom delimiters: space and comma
    auto tokens2 = sToken.Tokenize(L" ,");
    std::wcout << L"\nTokens with custom delimiters:" << std::endl;
    for (const auto& t : tokens2) {
        std::wcout << L"- " << t << std::endl;
    }
}

void TestStringIteratyor()
{
    std::cout << "string iter tests start.\n";

    SString s(L"Programming is মজার when you solve problems quickly!");

    // Range-based for loop works
    for (wchar_t ch : s) {
        std::wcout << ch << ' ';
    }
    std::wcout << std::endl;

    // STL algorithm works
    auto it = std::find(s.begin(), s.end(), L'W');
    if (it != s.end()) {
        std::wcout << L"Found character: " << *it << std::endl;
    }

    std::cout << "\nstring iter tests completed.\n";
}

void TestSPair()
{
    std::cout << "SPair iter tests start.\n";
    SPair<std::string, int> p1("Alice", 25);
    SPair<std::string, int> p2("Bob", 30);

    std::cout << p1.first << " is " << p1.second << " years old.\n";
    std::cout << p2.first << " is " << p2.second << " years old.\n";

    auto p3 = make_spair("Charlie", 35);
    std::cout << p3.first << " is " << p3.second << " years old.\n";

    if (p1 < p2)
    {
        std::cout << p1.first << " comes before " << p2.first << "\n";
    }

    std::cout << "SPair iter tests End.\n";
}

void TestTuple()
{
    std::cout << "STuple iter tests start.\n";
    STuple<std::string, int, double> t("Alice", 25, 72.5);

    std::cout << get<0>(t) << " is "
              << get<1>(t) << " years old, weight "
              << get<2>(t) << " kg.\n";

    STuple<> empty; // works too
    std::cout << "STuple iter tests End.\n";
}


