#include <cassert>
#include <iostream>

#include <cryptolibrium/cipher/playfair_cipher.hpp>

using cryptolibrium::cipher::PlayfairCipher;


// Helper function to test valid keys
void expectValidKey(const std::string& key, const std::string& testCaseDescription) {
    try {
        PlayfairCipher cipher(key);
        
        std::cout << "✓ " <<  testCaseDescription << " test passed." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "✗ " << testCaseDescription << " test failed: " << e.what() << std::endl;
        assert(false);  // Force a failure if an exception is thrown
    }
}


// Helper function to test invalid keys
void expectInvalidKey(const std::string& key, const std::string& testCaseDescription) {
    try {
        PlayfairCipher cipher(key);

        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        assert(false);  // Force a failure if no exception is thrown
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ " << testCaseDescription << " test passed: " << e.what() << std::endl;
    }
}


int main() {
    // Valid key
    expectValidKey("PLAYFAIR", "1.1 Valid key with uppercase letters");
    expectValidKey("playfair", "1.2 Valid key with lowercase letters");
    expectValidKey("PlayFair", "1.3 Valid key with mixed case letters");
    expectValidKey("A", "1.4 Valid key with one letter");
    expectValidKey("AABBC", "1.5 Valid key with duplicated letters");
    expectValidKey("A B C", "1.6 Valid key with spaces");
    
    // Invalid keys
    expectInvalidKey("", "1.7 Empty key");
    expectInvalidKey("PLAYFA1R", "1.8 Key with digits");
    expectInvalidKey("PLAYFAIR!", "1.9 Key with punctuation");
    expectInvalidKey("@#$%^&*", "1.10 Key with only symbols");
    expectInvalidKey("12345", "1.11 Key with only digits");
    expectInvalidKey("ыуауйа", "1.12 Key with non-Latin characters");
    expectInvalidKey(" ", "1.13 Key with only whitespace");

    // Encrypt && Decrypt tests
    PlayfairCipher playfairCipher("PLAYFAIR EXAMPLE");

    assert(playfairCipher.encrypt("HIDETHEGOLDINTHETREESTUMP") == "BMODZBXDNABEKUDMUIXMMOUVIF");
    assert(playfairCipher.decrypt("BMODZBXDNABEKUDMUIXMMOUVIF") == "HIDETHEGOLDINTHETREXESTUMP");
    
    assert(playfairCipher.decrypt(playfairCipher.encrypt("COMPUTER")) == "COMPUTER");
    assert(playfairCipher.decrypt(playfairCipher.encrypt("SECURITY")) == "SECURITY");
    assert(playfairCipher.decrypt(playfairCipher.encrypt("NETWORK")) == "NETWORKX");
    assert(playfairCipher.decrypt(playfairCipher.encrypt("PROGRAM")) == "PROGRAMX");
    assert(playfairCipher.decrypt(playfairCipher.encrypt("DATABASE")) == "DATABASE");

    assert(playfairCipher.decrypt(
           playfairCipher.encrypt("Hello World"))
       == "HELXLOWORLDX");

    assert(playfairCipher.decrypt(
           playfairCipher.encrypt("Computer Science"))
       == "COMPUTERSCIENCEX");

    assert(playfairCipher.decrypt(
           playfairCipher.encrypt("JIG"))
       == "IXIG");
}