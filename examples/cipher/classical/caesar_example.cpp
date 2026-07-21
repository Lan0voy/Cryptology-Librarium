#include <iostream>
#include <cryptolibrium/cipher/caesar_cipher.hpp>

int main() {
    std::cout << "Caesar Cipher Example" << std::endl;

    // Create a CaesarCipher object with a shift of 3
    cryptolibrium::cipher::CaesarCipher caesarCipher(3);

    // Input plaintext to be encrypted
    std::string plaintext;
    std::cout << "Enter the plaintext to encrypt: ";
    std::getline(std::cin, plaintext);

    // Encrypt the plaintext
    std::string ciphertext = caesarCipher.encrypt(plaintext);
    std::cout << "Encrypted text: " << ciphertext << std::endl;

    // Decrypt the ciphertext
    std::string decryptedText = caesarCipher.decrypt(ciphertext);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    return 0;
}