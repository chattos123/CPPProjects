#include "sHashTester.h"

// Private test functions
void sHashTester::TestHashMapStd() 
{
    std::cout << "\n*** testHashMapStd start ***\n";
    SHashMap<std::string, int> dict;
    dict.insert("Alice", 25);
    dict.insert("Bob", 30);
    dict.insert("Charlie", 35);

    dict.display();

    if (dict.contains("Bob"))
    {
        std::cout << "Bob's age: " << dict.at("Bob") << std::endl;
    }

    dict.erase("Alice");
    dict.display();
    std::cout << "*** testHashMapStd end ***\n";
}

void sHashTester::TestHashMapCustomHash()
{
    std::cout << "\n*** testHashMapCustomHash start ***\n";
    SHashMap<SString, int, SStringHash> dict;
    dict.insert(SString("Hello"), 100);
    dict.insert(SString("World"), 200);
    dict.insert(SString("DSA"), 300);

    dict.display();
    if (dict.contains(SString("World"))) {
        std::cout << "World's value: " << dict.at(SString("World")) << std::endl;
    }

    dict.insert(SString("Hello"), 111);
    dict.display();

    dict.erase(SString("DSA"));
    dict.display();
    std::cout << "*** testHashMapCustomHash end ***\n";
}

void sHashTester::TestHashMapCollision() {
    std::cout << "\n*** testHashMapCollision start ***\n";
    struct BadHash {
        std::size_t operator()(const SString& s) const noexcept { return 1; }
    };

    SHashMap<SString, int, BadHash> dict(4);
    dict.insert(SString("Key1"), 10);
    dict.insert(SString("Key2"), 20);
    dict.insert(SString("Key3"), 30);

    dict.display();
    std::cout << "Key1 -> " << dict.at(SString("Key1")) << std::endl;
    std::cout << "Key2 -> " << dict.at(SString("Key2")) << std::endl;
    std::cout << "Key3 -> " << dict.at(SString("Key3")) << std::endl;

    dict.erase(SString("Key2"));
    dict.display();
    std::cout << "*** testHashMapCollision end ***\n";
}

void sHashTester::TestSMapDictionary()
{
    std::cout << "SMapDirectory tests start.\n";
    SMapDictionary<std::string, int> dict;
    dict.insert("Alice", 25);
    dict.insert("Bob", 30);
    dict.insert("Charlie", 35);

    dict.display(); // { Alice: 25, Bob: 30, Charlie: 35 }

    std::cout << "Bob's age: " << dict.at("Bob") << std::endl;

    dict.erase("Alice");
    dict.display(); // { Bob: 30, Charlie: 35 }
    std::cout << "SMapDirectory tests End.\n";
}


// Public RunAllTests
void sHashTester::RunAllTests() {
    std::cout << "\n==============================\n";
    std::cout << "Running all SHashMap tests...\n";
    std::cout << "==============================\n";

    TestHashMapStd();
    TestHashMapCustomHash();
    TestHashMapCollision();
    TestSMapDictionary();

    std::cout << "\n==============================\n";
    std::cout << "All tests completed successfully.\n";
    std::cout << "==============================\n";
}
