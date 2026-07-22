#include <cryptolibrium/cipher/caesar_cipher.hpp>

namespace cryptolibrium::cipher {
    static constexpr int AlphabetSize = 26;  // Number of letters in the English alphabet

    // Constructor to initialize the CaesarCipher with a specific shift value
    CaesarCipher::CaesarCipher(int shift) : shift_(shift) {}

    // Encrypt the input plaintext using the Caesar cipher technique
    std::string CaesarCipher::encrypt(const std::string& plaintext) const {
        std::string ciphertext;
        for (char symbol : plaintext) {
            if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z') {

                // isupper - checks if the character is an uppercase letter (A-Z) 
                char base = std::isupper(static_cast<unsigned char>(symbol)) ? 'A' : 'a';
                
                // Shift the character by the specified shift value, wrapping around the alphabet
                //         + base: save register uppercase or lowercase letter
                //  symbol - base: convert character to 0-25 range
                //       + shift_: apply the shift value
                // % AlphabetSize: wrap around the alphabet
                symbol = (symbol - base + shift_) % AlphabetSize + base;
            }
            ciphertext += symbol;
        }
        return ciphertext;
    }

    // Decrypt the input ciphertext using the Caesar cipher technique
    std::string CaesarCipher::decrypt(const std::string& ciphertext) const {
        std::string plaintext;
        for (char symbol : ciphertext) {
            // Check if the character is an alphabet letter (A-Z or a-z)
            if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z') {

                // isupper - checks if the character is an uppercase letter (A-Z)
                char base = std::isupper(static_cast<unsigned char>(symbol)) ? 'A' : 'a';

                // Shift the character back by the specified shift value, wrapping around the alphabet
                //         + base: save register uppercase or lowercase letter
                //  symbol - base: convert character to 0-25 range
                //       + shift_: apply the shift value
                // % AlphabetSize: wrap around the alphabet
                symbol = (symbol - base - shift_ + AlphabetSize) % AlphabetSize + base;
            }
            plaintext += symbol;
        }
        return plaintext;
    }
}