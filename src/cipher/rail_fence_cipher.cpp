// playfair_cipher.cpp

// Include necessary standard library headers
#include <stdexcept>

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
}