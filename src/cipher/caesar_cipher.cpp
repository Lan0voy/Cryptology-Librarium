#include <cryptolibrium/cipher/caesar_cipher.hpp>

namespace cryptolibrium::cipher {

    // Constructor to initialize the CaesarCipher with a specific shift value
    CaesarCipher::CaesarCipher(int shift) : shift_(shift) {}

    // Encrypt the input plaintext using the Caesar cipher technique
    std::string CaesarCipher::encrypt(const std::string& plaintext) const {
        std::string ciphertext;
        for (char c : plaintext) {
            // isalpha - checks if the character is an alphabet letter (A-Z or a-z)
            if (std::isalpha(static_cast<unsigned char>(c))) {

                // isupper - checks if the character is an uppercase letter (A-Z) 
                char base = std::isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';
                
                // Shift the character by the specified shift value, wrapping around the alphabet
                //   + base: save register uppercase or lowercase letter
                // c - base: convert character to 0-25 range
                // + shift_: apply the shift value
                //     % 26: wrap around the alphabet
                c = (c - base + shift_) % 26 + base;
            }
            ciphertext += c;
        }
        return ciphertext;
    }

    // Decrypt the input ciphertext using the Caesar cipher technique
    std::string CaesarCipher::decrypt(const std::string& ciphertext) const {
        std::string plaintext;
        for (char c : ciphertext) {
            // isalpha - checks if the character is an alphabet letter (A-Z or a-z)
            if (std::isalpha(static_cast<unsigned char>(c))) {

                // isupper - checks if the character is an uppercase letter (A-Z)
                char base = std::isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';

                // Shift the character back by the specified shift value, wrapping around the alphabet
                //   + base: save register uppercase or lowercase letter
                // c - base: convert character to 0-25 range
                // + shift_: apply the shift value
                //     % 26: wrap around the alphabet
                c = (c - base - shift_ + 26) % 26 + base;
            }
            plaintext += c;
        }
        return plaintext;
    }
}