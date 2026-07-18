# СryptologyLibrarium

**cryptolibrium** is a C++ library focused on cryptographic algorithms,
classical ciphers, encryption techniques and cryptanalysis tools.

The goal of this project is not only to provide implementations of
cryptographic algorithms, but also to create an educational environment
for studying how these algorithms work.

---

## Status

Currently under active development.

# Features

Currently supported:

## Classical ciphers

- Caesar cipher
- Vigenere cipher
- Substitution ciphers

## Symmetric encryption

- AES (planned)

## Asymmetric encryption

- RSA (planned)

## Cryptanalysis

- Frequency analysis
- Brute-force attacks
- Statistical analysis

## Hash algorithms

- SHA family (planned)

---

# Project structure
```text
cryptologyLibrarium
│
├── cryptolibrium
│   ├── include
│   │   └── cryptolibrium
│   │       ├── cipher
│   │       │   └── caesar_cipher.hpp
│   │       ├── hash
│   │       └── analysis
│   │
│   ├── src
│   │   └── cipher
│   │       └── caesar_cipher.cpp
│   │
│   └── CMakeLists.txt
│
├── examples
├── tests
├── docs
└── README.md
```

# Installation

## Requirements

- C++17 compatible compiler
- CMake 3.20+

## Build

```bash
git clone https://github.com/Lan0voy/CryptologyLibrarium.git

cd cryptologyLibrarium

mkdir build
cd build

cmake ..
cmake --build .
```

# Quick start

```cpp
#include <cryptolibrium/cipher/caesar_cipher.hpp>

#include <iostream>


int main()
{
    cryptolibrium::cipher::CaesarCipher cipher(3);

    auto encrypted = cipher.encrypt("HELLO");

    auto decrypted = cipher.decrypt(encrypted);


    std::cout << encrypted << '\n';
    std::cout << decrypted << '\n';
}
