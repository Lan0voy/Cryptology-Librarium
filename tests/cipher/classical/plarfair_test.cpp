#include <cassert>
#include <iostream>

#include <cryptolibrium/cipher/playfair_cipher.hpp>

using cryptolibrium::cipher::PlayfairCipher;

int main() {
    /*
    // Test cases for PlayfairCipher encryption and decryption
    PlayfairCipher playfairCipher("KEYWORD");

    // Test case 1: Basic encryption and decryption
    std::string plaintext1 = "HELLO";
    std::string ciphertext1 = playfairCipher.encrypt(plaintext1);
    assert(playfairCipher.decrypt(ciphertext1) == plaintext1);

    // Test case 2: Encryption and decryption with repeated letters
    std::string plaintext2 = "BALLOON";
    std::string ciphertext2 = playfairCipher.encrypt(plaintext2);
    assert(playfairCipher.decrypt(ciphertext2) == plaintext2);

    // Test case 3: Encryption and decryption with odd-length plaintext
    std::string plaintext3 = "CRYPTOGRAPHY";
    std::string ciphertext3 = playfairCipher.encrypt(plaintext3);
    assert(playfairCipher.decrypt(ciphertext3) == plaintext3);

    // Test case 4: Encryption and decryption with non-alphabetic characters
    std::string plaintext4 = "HELLO, WORLD!";
    std::string ciphertext4 = playfairCipher.encrypt(plaintext4);
    assert(playfairCipher.decrypt(ciphertext4) == plaintext4);

    // Test case 5: Empty string
    std::string plaintext5 = "";
    std::string ciphertext5 = playfairCipher.encrypt(plaintext5);
    assert(playfairCipher.decrypt(ciphertext5) == plaintext5);

    std::cout << "All tests passed!" << std::endl;
    */
}