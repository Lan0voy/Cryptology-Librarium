// railfence_cipher.hpp

// Include guard to prevent multiple inclusions of this header file
#pragma once

// Include necessary standard library headers
#include <string>
#include <cstddef>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium::cipher {

    // Define the RailFenceCipher class for encrypting and decrypting text using the Rail Fence cipher technique
    class RailFenceCipher {
        public:
        
            // Create Rail Fence Cipher with specified number of rails
            explicit RailFenceCipher(std::size_t rails);

            // Encrypt the input text using the Rail Fence Cipher
            [[nodiscard]]
            std::string encrypt(
                const std::string& plaintext
            ) const;
                    
            // Decrypt the input text using the Rail Fence Cipher
            [[nodiscard]]
            std::string decrypt(
                const std::string& ciphertext
            ) const;    


        private:
            // Number of rails for the Rail Fence Cipher
            const std::size_t rails_;

            // Validate the number of rails
            static void validateRails(std::size_t rails);
    };
}