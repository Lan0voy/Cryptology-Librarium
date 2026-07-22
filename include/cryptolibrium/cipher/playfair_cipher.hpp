// playfair_cipher.hpp

// Include guard to prevent multiple inclusions of this header file
#pragma once

// Include necessary standard library headers
#include <string>
#include <array>
#include <utility>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium::cipher {
    // Define the PlayfairCipher class for encrypting and decrypting text using the Playfair cipher technique
    class PlayfairCipher {
        public:

            // Create Playfair cipher with specified key
            explicit PlayfairCipher(std::string key);
        
            // Encrypt the input text using the Playfair cipher
            [[nodiscard]]
            std::string encrypt(
                const std::string& plaintext
            ) const;
            
            // Decrypt the input text using the Playfair cipher
            [[nodiscard]]
            std::string decrypt(
                const std::string& ciphertext
            ) const;

        private:            
            // Size of the Playfair key square.
            static constexpr std::size_t MatrixSize = 5;  

            // Represents the position of a character in the Playfair key square.
            struct Position {
                std::size_t row;
                std::size_t col;
            };

            // Keyword used to generate the Playfair key square.
            const std::string key_;

            // 5×5 Playfair key square.
            std::array<std::array<char, MatrixSize>, MatrixSize> matrix_;

            // Prepare the key by removing duplicates and non-alphabetic characters, and converting to uppercase.
            std::string prepareKey(const std::string& key) const;

            // Validate the key to ensure it meets the requirements for the Playfair cipher.
            void validateKey(const std::string& key) const;

            // Generate the Playfair key square from the keyword.
            void generateMatrix();

            // Normalize text and prepare Playfair digraphs for processing.
            std::string prepareText(const std::string& text) const;

            // Find the position of a character in the key square.
            Position findPosition(char c) const;

            // Encrypt a single Playfair digraph.
            std::pair<char, char> encryptPair(char first, char second) const;

            // Decrypt a single Playfair digraph.
            std::pair<char, char> decryptPair(char first, char second) const;
    };
}