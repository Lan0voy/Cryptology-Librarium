#include <iostream>
#include <cassert>

#include <cryptolibrium/cipher/rail_fence_cipher.hpp>

using cryptolibrium::cipher::RailFenceCipher;

// Helper function to test valid keys
void expectValidKey(const std::size_t& key, const std::string& testCaseDescription) {
    try {
        RailFenceCipher cipher(key);
        
        std::cout << "✓ " <<  testCaseDescription << " test passed." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "✗ " << testCaseDescription << " test failed: " << e.what() << std::endl;
        assert(false);  // Force a failure if an exception is thrown
    }
}


// Helper function to test invalid keys
void expectInvalidKey(const std::size_t& key, const std::string& testCaseDescription) {
    try {
        RailFenceCipher cipher(key);

        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        assert(false);  // Force a failure if no exception is thrown
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ " << testCaseDescription << " test passed: " << e.what() << std::endl;
    }
}

// Helper function to test Rail-Fence-Cipher encrypt
void expectEncrypt(const std::size_t& rails, const std::string& plaintext, const std::string& ciphertext, const std::string& testCaseDescription) {
    RailFenceCipher cipher(rails);

    if (cipher.encrypt(plaintext) == ciphertext) {
       std::cout << "✓ " <<  testCaseDescription << " test passed." << std::endl;
    } else {
        std::cerr << "✗ " << testCaseDescription << " test failed." << std::endl;
        assert(false);
    }
}

int main() {
    // =========================
    // 1. Rails Validation Tests
    // =========================

    // Invalid rails
    expectInvalidKey(0, "1.1 key = 0");
    expectInvalidKey(1, "1.2 key < 2");

    // Valid rails
    expectValidKey(4, "1.3 Valid key >= 2");

    // =========================
    // 2. Encryption Tests
    // =========================

    // 2.1 Empty string
    expectEncrypt(
        3,
        "",
        "",
        "2.1 Empty string"
    );

    // 2.2 Single character
    expectEncrypt(
        3,
        "A",
        "A",
        "2.2 Single character"
    );

    // 2.3 Two characters
    expectEncrypt(
        3,
        "AB",
        "AB",
        "2.3 Two characters"
    );

    // 2.4 Three characters
    expectEncrypt(
        3,
        "ABC",
        "ABC",
        "2.4 Three characters"
    );

    // 2.5 Classic Rail Fence example
    expectEncrypt(
        3,
        "WEAREDISCOVEREDFLEEATONCE",
        "WECRLTEERDSOEEFEAOCAIVDEN",
        "2.5 Classic example"
    );

    // 2.6 HELLOWORLD (3 rails)
    expectEncrypt(
        3,
        "HELLOWORLD",
        "HOLELWRDLO",
        "2.6 HELLOWORLD (3 rails)"
    );

    // 2.7 HELLOWORLD (2 rails)
    expectEncrypt(
        2,
        "HELLOWORLD",
        "HLOOLELWRD",
        "2.7 HELLOWORLD (2 rails)"
    );

    // 2.8 Spaces
    expectEncrypt(
        3,
        "HELLO WORLD",
        "HOREL OLLWD",
        "2.8 Spaces"
    );

    // 2.9 Digits
    expectEncrypt(
        3,
        "ABC123XYZ",
        "A2ZB13YCX",
        "2.9 Digits"
    );

    // 2.10 Punctuation
    expectEncrypt(
        3,
        "HELLO!",
        "HOEL!L",
        "2.10 Punctuation"
    );

    // 2.11 Mixed characters
    expectEncrypt(
        3,
        "Hello, World! 123",
        "Hoo!3el,Wrd 2l l1",
        "2.11 Mixed characters"
    );

    // 2.12 Punctuation only
    expectEncrypt(
        3,
        "!@#$%^&*",
        "!%@$^*#&",
        "2.12 Punctuation only"
    );

    // 2.13 Digits only
    expectEncrypt(
        4,
        "123456789",
        "172683594",
        "2.13 Digits only"
    );

    // 2.14 Long repeated pattern
    expectEncrypt(
        5,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "AIQYBHJPRXZCGKOSWDFLNTVEMU",
        "2.14 Alphabet"
    );

    // 2.15 Rails > plaintext length
    expectEncrypt(
        100,
        "HELLO",
        "HELLO",
        "2.15 Rails > plaintext length"
    );

    // 2.16 Rails == plaintext
    expectEncrypt(
        5,
        "HELLO",
        "HELLO",
        "2.16 Rails == plaintext length"
    );
}