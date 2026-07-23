#include <iostream>
#include <cryptolibrium/cipher/playfair_cipher.hpp>

int main() {
    try {
        // Create a Playfair cipher with the specified key
        cryptolibrium::cipher::PlayfairCipher playfairCipher("PLAYFAIR EXAMPLE");

        std::string plaintext = "Hide the gold in the tree stump";

        // Encrypt plaintext
        std::string ciphertext = playfairCipher.encrypt(plaintext);

        // Decrypt ciphertext
        std::string decryptedText = playfairCipher.decrypt(ciphertext);

        std::cout << "Key:        PLAYFAIR EXAMPLE\n";
        std::cout << "Plaintext:  " << plaintext << '\n';
        std::cout << "Ciphertext: " << ciphertext << '\n';
        std::cout << "Decrypted:  " << decryptedText << '\n';

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}