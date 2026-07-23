# Playfair Cipher

## Overview

The **Playfair cipher** is a classical symmetric encryption algorithm invented in **1854** by Charles Wheatstone and later promoted by Lord Playfair. Unlike the Caesar or Vigenère ciphers, the Playfair cipher encrypts **pairs of letters (digraphs)** rather than individual characters, making simple frequency analysis significantly more difficult.

This implementation follows the **classical Playfair cipher** using a **5 × 5 key square**, where the letters **I** and **J** share the same position.

---

# Features

* Classical 5 × 5 Playfair cipher implementation
* Case-insensitive input
* Preserves only English alphabetic characters
* Automatically converts lowercase letters to uppercase
* Replaces **J** with **I**
* Automatically inserts **X** between duplicate letters in a digraph
* Automatically appends **X** if the prepared plaintext contains an odd number of letters
* Supports both encryption and decryption
* Throws descriptive exceptions for invalid input

---

# Public Interface

```cpp
explicit PlayfairCipher(const std::string& key);

std::string encrypt(const std::string& plaintext) const;

std::string decrypt(const std::string& ciphertext) const;
```

---

# Constructor

```cpp
PlayfairCipher(const std::string& key);
```

Constructs a Playfair cipher object using the specified key.

The constructor validates and normalizes the key before generating the 5 × 5 key square.

---

# Key Requirements

The key:

* must not be empty;
* must contain at least one English letter;
* may contain uppercase or lowercase English letters;
* may contain whitespace characters;
* must not contain digits;
* must not contain punctuation;
* must not contain non-English letters.

Example of valid keys:

```text
PLAYFAIR EXAMPLE
MONARCHY
Secret Key
```

Invalid keys:

```text
PLAYFAIR123
Secret!
Ключ
```

---

# Key Normalization

Before constructing the key square, the key is normalized.

The following operations are performed:

1. Convert all letters to uppercase.
2. Replace every **J** with **I**.
3. Remove whitespace.
4. Remove duplicate letters while preserving their first occurrence.
5. Append the remaining unused letters of the English alphabet.

The alphabet used is:

```text
ABCDEFGHIKLMNOPQRSTUVWXYZ
```

Notice that the letter **J** is omitted.

---

# Key Square Example

Key:

```text
PLAYFAIR EXAMPLE
```

Produces the following key square:

```text
P L A Y F
I R E X M
B C D G H
K N O Q S
T U V W Z
```

---

# Plaintext Preparation

Before encryption, plaintext is normalized.

The following steps are performed:

### 1. Remove non-letter characters

Only English letters are preserved.

Example:

```text
Hello, World!
```

↓

```text
HELLOWORLD
```

---

### 2. Convert to uppercase

```text
hello
```

↓

```text
HELLO
```

---

### 3. Replace J with I

```text
JIG
```

↓

```text
IIG
```

---

### 4. Split into digraphs

Example:

```text
HELLOWORLD
```

↓

```text
HE LL OW OR LD
```

---

### 5. Insert X between duplicate letters

Duplicate letters are not allowed inside one digraph.

Example:

```text
HELLO
```

↓

```text
HELXLO
```

---

### 6. Append X if necessary

If the resulting plaintext contains an odd number of letters, an additional **X** is appended.

Example:

```text
NETWORK
```

↓

```text
NETWORKX
```

---

# Encryption Rules

Each digraph is encrypted independently.

There are three possible cases.

---

## Case 1

Both letters are located in the same row.

Move each letter one position to the right.

```text
A B C D E
```

↓

```text
B C D E A
```

---

## Case 2

Both letters are located in the same column.

Move each letter one position downward.

```text
A
B
C
D
E
```

↓

```text
B
C
D
E
A
```

---

## Case 3

The letters form the corners of a rectangle.

Replace each letter with the letter located in the same row but in the column of the other letter.

```text
A . B
. . .
C . D
```

↓

```text
B . A
. . .
D . C
```

---

# Decryption Rules

Decryption performs the inverse operations.

### Same row

Move left.

### Same column

Move up.

### Rectangle

Swap columns exactly as during encryption.

---

# Ciphertext Validation

Before decryption the ciphertext is validated.

The ciphertext:

* must not be empty;
* must contain at least two letters;
* must contain an even number of letters;
* may contain whitespace;
* must contain only English alphabetic characters.

---

# Important Note About Decryption

The Playfair cipher is **not perfectly reversible**.

During plaintext preparation, additional **X** characters may be inserted.

For example

```text
HELLO
```

becomes

```text
HELXLO
```

After decryption the library returns

```text
HELXLO
```

instead of

```text
HELLO
```

because it is impossible to determine whether an **X** was originally present in the message or inserted automatically.

Therefore,

```cpp
decrypt(encrypt(text))
```

returns the **prepared plaintext**, not necessarily the original plaintext.

This behavior follows the classical Playfair cipher specification.

---

# Example

```cpp
#include <iostream>
#include <cryptolibrium/cipher/playfair_cipher.hpp>

int main()
{
    cryptolibrium::cipher::PlayfairCipher playfair("PLAYFAIR EXAMPLE");

    std::string plaintext = "Hide the gold in the tree stump";

    std::string ciphertext = playfair.encrypt(plaintext);

    std::string decrypted = playfair.decrypt(ciphertext);

    std::cout << "Key:        PLAYFAIR EXAMPLE\n";
    std::cout << "Plaintext:  " << plaintext << '\n';
    std::cout << "Ciphertext: " << ciphertext << '\n';
    std::cout << "Decrypted:  " << decrypted << '\n';
}
```

Output:

```text
Key:        PLAYFAIR EXAMPLE
Plaintext:  Hide the gold in the tree stump
Ciphertext: BMODZBXDNABEKUDMUIXMMOUVIF
Decrypted:  HIDETHEGOLDINTHETREXESTUMP
```

---

# Complexity

| Operation             | Complexity |
| --------------------- | ---------: |
| Key generation        |       O(1) |
| Plaintext preparation |       O(n) |
| Encryption            |       O(n) |
| Decryption            |       O(n) |

where **n** is the number of characters in the processed text.

---

# Exceptions

The library throws `std::invalid_argument` if:

* the key is empty;
* the key contains invalid characters;
* the plaintext is empty;
* the ciphertext is empty;
* the ciphertext contains an odd number of letters;
* the ciphertext contains invalid characters.

A `std::logic_error` is thrown if an internal inconsistency occurs (for example, a character cannot be found in the generated key square).

---

# References

* Charles Wheatstone, *The Playfair Cipher* (1854)
* Helen Fouché Gaines, *Cryptanalysis* (1939)
* David Kahn, *The Codebreakers* (1967)
