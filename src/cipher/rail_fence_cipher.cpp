// playfair_cipher.cpp

// Include necessary standard library headers
#include <stdexcept>
#include <cstddef>
#include <string>
#include <vector>

// Include the header file for the PlayfairCipher class
#include <cryptolibrium/cipher/rail_fence_cipher.hpp>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium {
    // Implement the constructor for the Rail Fence Cipher class, which initializes rails
    cipher::RailFenceCipher::RailFenceCipher(std::size_t rails) : rails_(rails) {
        validateRails(rails_);  // Validate the rails number to ensure it meets the requirements
    }


    // Implementation for validating number of rails
    // This function will throw an exception if the rails is invalid
    void cipher::RailFenceCipher::validateRails(std::size_t rails) {
        // Ensure that the number of rails is at least 2.           
        if (rails < 2) {
            throw std::invalid_argument("The number of rails must be at least 2.");
        }
    }


    // Implementation for encrypting the input text using the Rail Fence Cipher
    // This function will return the encrypted ciphertext  
    std::string cipher::RailFenceCipher::encrypt(const std::string& plaintext) const {
        const std::size_t plaintextLength = plaintext.length();
        bool movingDown = true;
        std::vector<std::string> encryptedRails(rails_);

        // Distribute characters across the rails.
        for (std::size_t i = 0, currentRail = 0; i < plaintextLength; ++i) {
            // Append the current character to the active rail.
            encryptedRails[currentRail] += plaintext[i];

            // up or bottom border
            if (currentRail == rails_ - 1) {
                movingDown = false;
            }
            else if (currentRail == 0) {
                movingDown = true;
            }

            // next rail
            if (movingDown) {++currentRail;} else {--currentRail;}
        }

        /*
            Another algorithms, more math:
            
            std::size_t period = 2 * (rails_ - 1);
            std::size_t rail = i % period;

            if (rail >= rails_) {
                rail = period - rail;
            }
            */


        // Concatenate all rails to produce the ciphertext.
        std::string ciphertext;

        for (const auto& rail : encryptedRails) {
            ciphertext += rail;
        }

        return ciphertext;
    }


    // Implementation for decrypting the input text using the Playfair cipher
    // This function will return the decrypted plaintext    
    std::string cipher::RailFenceCipher::decrypt(const std::string& ciphertext) const {
        std::vector<std::size_t> symbolsInRails(rails_);
        std::vector<std::size_t> railsRoute;
        std::size_t ciphertextLength = ciphertext.length();
        bool movingDown = true;

        // 1. Generate rail pattern
        for (std::size_t i = 0, currentRail = 0; i < ciphertextLength; ++i) {
            //railsRoute += currentRail;
            railsRoute.push_back(currentRail);
            
            // up or bottom border
            if (currentRail == rails_ - 1) {
                movingDown = false;
            }
            else if (currentRail == 0) {
                movingDown = true;
            }

            // next rail
            if (movingDown) {++currentRail;} else {--currentRail;}            
        }

        // 2. Count number of symbols in each rail
        for (std::size_t i = 0; i < ciphertextLength; ++i) {
            symbolsInRails[railsRoute[i]]++;
        }

        // 3. Split ciphertext into rails
        std::vector<std::string> railText(rails_);
        std::size_t tmpIndex = 0;

        for (std::size_t i = 0; i < rails_; ++i) {
            for (std::size_t j = 0; j < symbolsInRails[i]; ++j) {
                railText[i] += ciphertext[tmpIndex];
                tmpIndex++;
            }
        }

        // 4. Reconstruct plaintext following the rail route
        std::string decryptedText;
        std::vector<size_t> currentSymbolInRail(rails_);

        for (std::size_t rail : railsRoute) {
            decryptedText += railText[rail][currentSymbolInRail[rail]];
            ++currentSymbolInRail[rail];
        }

        return decryptedText;
    }
}