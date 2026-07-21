# Caesar Cipher

## Overview

The Caesar cipher is one of the oldest and simplest encryption algorithms in classical cryptography. It is a monoalphabetic substitution cipher where each alphabetic character in the plaintext is shifted by a fixed number of positions in the alphabet.

Originally attributed to Julius Caesar, the cipher was used to protect military communications by replacing each letter with another letter a fixed distance away in the alphabet.

For example, with a shift value of **3**:

```text
Plaintext : ABCDEFGHIJKLMNOPQRSTUVWXYZ
Ciphertext: DEFGHIJKLMNOPQRSTUVWXYZABC
```

Although historically significant, the Caesar cipher is **not considered cryptographically secure** and should only be used for educational purposes.

---

## Features

- Classical monoalphabetic substitution cipher.
- Configurable shift value.
- Supports uppercase and lowercase English letters.
- Preserves the original letter case.
- Leaves digits, whitespace, punctuation, and other non-alphabetic characters unchanged.
- Linear time complexity.

---

## Mathematical Definition

Let

- **x** be the zero-based alphabet index of a letter.
- **k** be the shift value.

Encryption:

```
E(x) = (x + k) mod 26
```

Decryption:

```
D(x) = (x - k + 26) mod 26
```

The additional **+26** ensures that the result remains non-negative before applying the modulo operation.

---

## API

### Constructor

```cpp
explicit CaesarCipher(int shift);
```

Creates a Caesar cipher with the specified shift value.

#### Parameters

| Name | Description |
|------|-------------|
| shift | Number of positions used for character shifting. |

---

### encrypt()

```cpp
std::string encrypt(const std::string& plaintext) const;
```

Encrypts the provided plaintext using the configured shift.

#### Parameters

| Name | Description |
|------|-------------|
| plaintext | Input text to encrypt. |

#### Returns

Encrypted string.

---

### decrypt()

```cpp
std::string decrypt(const std::string& ciphertext) const;
```

Decrypts ciphertext produced by the Caesar cipher.

#### Parameters

| Name | Description |
|------|-------------|
| ciphertext | Text to decrypt. |

#### Returns

Original plaintext.

---

## Example

```cpp
#include <iostream>
#include <cryptolibrium/cipher/caesar_cipher.hpp>

int main()
{
    cryptolibrium::cipher::CaesarCipher cipher(3);

    std::string plaintext = "Hello, World!";

    auto encrypted = cipher.encrypt(plaintext);
    auto decrypted = cipher.decrypt(encrypted);

    std::cout << "Plaintext : " << plaintext << '\n';
    std::cout << "Encrypted: " << encrypted << '\n';
    std::cout << "Decrypted: " << decrypted << '\n';
}
```

Output:

```text
Plaintext : Hello, World!
Encrypted: Khoor, Zruog!
Decrypted: Hello, World!
```

---

## Complexity

| Operation | Complexity |
|-----------|------------|
| Encryption | O(n) |
| Decryption | O(n) |
| Memory | O(1) |

where **n** is the length of the input string.

---

## Limitations

- Supports only the English alphabet (A-Z, a-z).
- Does not provide real cryptographic security.
- Vulnerable to brute-force attacks.
- Vulnerable to frequency analysis.
- Intended solely for educational and demonstration purposes.

---

## Historical Background

The Caesar cipher is traditionally attributed to **Julius Caesar**, who reportedly used it to protect military correspondence. Because there are only 25 possible non-trivial shifts, the cipher can be broken almost instantly using exhaustive search and serves primarily as an introductory example in the study of classical cryptography.

---

## References

1. David Kahn — *The Codebreakers*.
2. Simon Singh — *The Code Book*.
3. William Stallings — *Cryptography and Network Security*.
