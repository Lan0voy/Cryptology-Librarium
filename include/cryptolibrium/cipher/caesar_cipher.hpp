// caesar_cipher.hpp

// Include guard to prevent multiple inclusions of this header file
#pragma once    

// Include necessary standard library headers
#include <string>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium::cipher {

    // Define the CaesarCipher class for encrypting and decrypting text using the Caesar cipher technique
    class CaesarCipher {
        public:

            // Create Caesar cipher with specified shift key
            explicit CaesarCipher(int shift);
        
            // Encrypt the input text using the Caesar cipher
            [[nodiscard]]
            std::string encrypt(
                const std::string& plaintext
            ) const;
            
            // Decrypt the input text using the Caesar cipher
            [[nodiscard]]
            std::string decrypt(
                const std::string& ciphertext
            ) const;


        private:
            // Store the shift value for the Caesar cipher
            int shift_;
    };
}