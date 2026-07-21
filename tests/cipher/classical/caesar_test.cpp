#include <iostream>
#include <cassert>

#include <cryptolibrium/cipher/caesar_cipher.hpp>

using cryptolibrium::cipher::CaesarCipher;

int main() {
    CaesarCipher caesarCipher(3);

    // Test cases for CaesarCipher encryption and decryption
    assert(caesarCipher.encrypt("HELLO") == "KHOOR");
    assert(caesarCipher.decrypt("KHOOR") == "HELLO");

    // Additional test cases
    assert(caesarCipher.encrypt("WORLD") == "ZRUOG");
    assert(caesarCipher.decrypt("ZRUOG") == "WORLD");

    // Test case with mixed case letters
    assert(caesarCipher.encrypt("CRYPTOGRAPHY") == "FUBSWRJUDSKB");
    assert(caesarCipher.decrypt("FUBSWRJUDSKB") == "CRYPTOGRAPHY");

    // Test case with wrap-around for uppercase letters
    assert(caesarCipher.encrypt("XYZ") == "ABC");
    assert(caesarCipher.decrypt("ABC") == "XYZ");

    // Test case with wrap-around for lowercase letters
    assert(caesarCipher.encrypt("xyz") == "abc");
    assert(caesarCipher.decrypt("abc") == "xyz");

    // Test case with non-alphabetic characters (should remain unchanged)
    assert(caesarCipher.encrypt("Hello World") == "Khoor Zruog");
    assert(caesarCipher.decrypt("Khoor Zruog") == "Hello World");

    // Test case with empty string
    assert(caesarCipher.encrypt("") == "");
    assert(caesarCipher.decrypt("") == "");

    // Test case with a string containing numbers and special characters
    std::string text = "Hello World! 123";
    assert(
        caesarCipher.decrypt(caesarCipher.encrypt(text)) == text
    );

    std::cout << "All tests passed!" << std::endl;
}