// playfair_cipher.cpp

// Include necessary standard library headers
#include <stdexcept>

// Include the header file for the PlayfairCipher class
#include <cryptolibrium/cipher/playfair_cipher.hpp>

// Define the namespace for the cryptolibrium library and its cipher module
namespace cryptolibrium {
    // Implement the constructor for the PlayfairCipher class, which initializes the key and generates the key square
    cipher::PlayfairCipher::PlayfairCipher(std::string key) : key_(std::move(key)) {
        validateKey(key_);  // Validate the key to ensure it meets the requirements
        generateMatrix();   // Generate the Playfair key square based on the provided key
    }


    // Implementation for validating the key to ensure it meets the requirements for the Playfair cipher
    // This function will throw an exception if the key is invalid
    void cipher::PlayfairCipher::validateKey(const std::string& key) const {
        // Check if the key is empty and throw an exception if it is
        if (key.empty()) {
            throw std::invalid_argument("Key cannot be empty.");
        }

        int letterCounter = 0;

        // Check if the characters are alphabetic or a whitespace character (space, tab, newline)
        for (char symbol : key) {
            const bool isUpper = symbol >= 'A' && symbol <= 'Z';
            const bool isLower = symbol >= 'a' && symbol <= 'z';
            const bool isWhitespace = symbol == ' ' || symbol == '\t' || symbol == '\n';

            if (!isUpper && !isLower && !isWhitespace) {
                throw std::invalid_argument("Key must contain only English alphabetic characters and whitespaces.");
            }

            if (isUpper || isLower) {
                ++letterCounter;
            }
        }

        // Check if the key contains at least one letter and throw an exception if it does not
        if (letterCounter == 0) {
            throw std::invalid_argument("Key must contain at least one letter.");
        }
    }
    
    
    // Implementation for validating the encrypted text to ensure it meets the requirements for the Playfair decrypt function
    // This function will throw an exception if text is invalid
    void cipher::PlayfairCipher::validateCipherText(const std::string& cipherText) const {
        if (cipherText.empty()) {
            throw std::invalid_argument("Encrypted text cannot be empty.");
        }

        int letterCounter = 0;

        // Check if the characters are alphabetic (not 'J') or a whitespace character (space, tab, newline)
        for (char symbol : cipherText) {
            const bool isUpper = symbol >= 'A' && symbol <= 'Z';
            const bool isLower = symbol >= 'a' && symbol <= 'z';
            const bool isWhitespace = symbol == ' ' || symbol == '\t' || symbol == '\n';

            if (!isUpper && !isLower && !isWhitespace) {
                throw std::invalid_argument("Encrypted text must contain only English alphabetic characters and whitespaces.");
            }

            if (isUpper || isLower) {
                ++letterCounter;
            }
        }

        // Check if the key contains at least two letters and throw an exception if it does not
        if ((letterCounter < 2) || (letterCounter % 2 != 0)) {
            throw std::invalid_argument("Encrypted text must contain even number of letters, at least two.");
        }
    }


    // Implementation for preparing the key by removing duplicates and non-alphabetic characters, and converting to uppercase
    // This function will return a cleaned-up version of the key suitable for generating the key square  
    std::string cipher::PlayfairCipher::prepareKey(const std::string& key) const {
        std::string uppercaseKey = key;

        // Convert each character to uppercase && change J -> I
        for (char& symbol : uppercaseKey) {
            symbol = std::toupper(static_cast<unsigned char>(symbol));

            // Replace 'J' with 'I' for Playfair cipher
            if (symbol == 'J') {
                symbol = 'I';
            }
        }

        std::string preparedKey;

        // Only add alphabetic characters that are not already in the prepared key
        for (char symbol : uppercaseKey) {
            if ((symbol >= 'A' && symbol <= 'Z') && (preparedKey.find(symbol) == std::string::npos)) {
                preparedKey += symbol;
            }
        }

        return preparedKey;
    }


    // Implementation for generating the Playfair key square from the keyword
    // This function will fill the matrix_ member variable based on the key_   
    void cipher::PlayfairCipher::generateMatrix() {  
        // Normalize the key by preparing it
        std::string preparedKey = prepareKey(key_);
        
        // Fill the matrix with the prepared key and remaining letters of the alphabet
        // 'J' is typically omitted in Playfair cipher
        static constexpr std::string_view alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 

        // Index to track the position in the matrix 
        std::size_t index = 0;      
        // Fill the matrix with the prepared key
        for (char symbol : preparedKey) {
            // Calculate the row and column in the matrix based on the index
            matrix_[index / MatrixSize][index % MatrixSize] = symbol;
            ++index;
        }

        // Fill the remaining positions with the rest of the alphabet
        for (char symbol : alphabet) {
            // Only add characters that are not already used in the key
            if (preparedKey.find(symbol) == std::string::npos) {
                matrix_[index / MatrixSize][index % MatrixSize] = symbol;
                ++index;
            }
        }
    }


    // Implementation for normalizing text and preparing Playfair digraphs
    // This function will return a string that is ready for encryption or decryption
    std::string cipher::PlayfairCipher::preparePlaintext(const std::string& text) const {
        std::string preparedText = "";

        // Convert each character to uppercase && change J -> I
        for (char symbol : text) {
            if (((symbol >= 'A') && (symbol <= 'Z')) || ((symbol >= 'a') && (symbol <= 'z'))) {
                symbol = std::toupper(static_cast<unsigned char>(symbol));

                // Replace 'J' with 'I' for Playfair cipher
                if (symbol == 'J') {
                    symbol = 'I';
                }

                preparedText += symbol;
            }
        }

        // Additional 'X' for bigrams
        std::size_t textLength = preparedText.size();

        for (std::size_t i = 0; i + 1 < textLength; i += 2) {
            if (preparedText[i] == preparedText[i + 1]) {
                preparedText.insert(i + 1, 1, 'X');
                textLength++;
            }
        }

        if (textLength % 2 == 1) {
            preparedText += 'X';
        }


        return preparedText;
    }

    // Implementation for normalizing text and preparing Playfair digraphs
    // This function will return a string that is ready for encryption or decryption
    std::string cipher::PlayfairCipher::prepareCiphertext(const std::string& ciphertext) const {
        std::string preparedText = "";

        // Convert each character to uppercase && change J -> I
        // Remove non-alphabetic characters
        for (char symbol : ciphertext) {
            if (((symbol >= 'A') && (symbol <= 'Z')) || ((symbol >= 'a') && (symbol <= 'z'))) {
                symbol = std::toupper(static_cast<unsigned char>(symbol));

                // Replace 'J' with 'I' for Playfair cipher
                if (symbol == 'J') {
                    symbol = 'I';
                }

                preparedText += symbol;
            }
        }

        return preparedText;
    }   



    // Implementation for finding the position of a character in the key square
    // This function will return a Position struct indicating the row and column of the character
    cipher::PlayfairCipher::Position cipher::PlayfairCipher::findPosition(char symbol) const {
        Position pos;

        for (size_t i = 0; i < MatrixSize; ++i) {
            for (size_t j = 0; j < MatrixSize; ++j) {
                if (matrix_[i][j] == symbol) {
                    pos.row = i;
                    pos.col = j;
                    return pos;
                }
            }
        }

        throw std::logic_error("Character not found in Playfair matrix.");
    }

    
    // Implementation for encrypting a single Playfair digraph
    // This function will return a pair of characters representing the encrypted digraph 
    std::pair<char, char> cipher::PlayfairCipher::encryptPair(char first, char second) const {
        Position firstPos = findPosition(first);
        Position secondPos = findPosition(second);

        std::pair<char, char> digraph
        ;
        // 1 case: diff rows and cols
        if ((firstPos.row != secondPos.row) && (firstPos.col != secondPos.col)) {
            digraph.first = matrix_[firstPos.row][secondPos.col];
            digraph.second = matrix_[secondPos.row][firstPos.col];
        }

        // 2 case: same rows -> move right by 1
        if (firstPos.row == secondPos.row) {
            digraph.first = matrix_[firstPos.row][(firstPos.col + 1) % MatrixSize];
            digraph.second = matrix_[secondPos.row][(secondPos.col + 1) % MatrixSize];
        }

        // 3 case: same cols -> move down by 1
        if (firstPos.col == secondPos.col) {
            digraph.first = matrix_[(firstPos.row + 1) % MatrixSize][firstPos.col];
            digraph.second = matrix_[(secondPos.row + 1) % MatrixSize][secondPos.col];
        }


        return digraph;
    }

    
    // Implementation for decrypting a single Playfair digraph
    // This function will return a pair of characters representing the decrypted digraph
    std::pair<char, char> cipher::PlayfairCipher::decryptPair(char first, char second) const {
        Position firstPos = findPosition(first);
        Position secondPos = findPosition(second);

        std::pair<char, char> digraph;

        // 1 case: diff rows and cols
        if ((firstPos.row != secondPos.row) && (firstPos.col != secondPos.col)) {
            digraph.first = matrix_[firstPos.row][secondPos.col];
            digraph.second = matrix_[secondPos.row][firstPos.col];
        }

        // 2 case: same rows -> move left by 1
        if (firstPos.row == secondPos.row) {
            digraph.first = matrix_[firstPos.row][(firstPos.col + MatrixSize - 1) % MatrixSize];
            digraph.second = matrix_[secondPos.row][(secondPos.col + MatrixSize - 1) % MatrixSize];
        }

        // 3 case: same cols -> move up by 1
        if (firstPos.col == secondPos.col) {
            digraph.first = matrix_[(firstPos.row + MatrixSize - 1) % MatrixSize][firstPos.col];
            digraph.second = matrix_[(secondPos.row + MatrixSize - 1) % MatrixSize][secondPos.col];
        }
   
        return digraph;
    }
    
    
    // Implementation for encrypting the input text using the Playfair cipher
    // This function will return the encrypted ciphertext  
    std::string cipher::PlayfairCipher::encrypt(const std::string& plaintext) const {
        std::string preparedText = preparePlaintext(plaintext);
        std::string encryptedText;

        size_t preparedTextLength = preparedText.size();
        std::pair<char, char> digraph;

        for (size_t i = 0; i < preparedTextLength; i += 2) {
            digraph = encryptPair(preparedText[i], preparedText[i+1]);

            encryptedText.push_back(digraph.first);
            encryptedText.push_back(digraph.second);
        }

        return encryptedText;
    }


    // Implementation for decrypting the input text using the Playfair cipher
    // This function will return the decrypted plaintext    
    std::string cipher::PlayfairCipher::decrypt(const std::string& ciphertext) const {
        validateCipherText(ciphertext);
        std::string preparedText = prepareCiphertext(ciphertext);
        std::string decryptedText;

        size_t preparedTextLength = preparedText.size();
        std::pair <char, char> digraph;

        for (size_t i = 0; i < preparedTextLength; i += 2) {
             digraph = decryptPair(preparedText[i], preparedText[i+1]);

             decryptedText.push_back(digraph.first);
             decryptedText.push_back(digraph.second);
        }

        return decryptedText;
    }
}