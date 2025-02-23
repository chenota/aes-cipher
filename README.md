# AES Cipher

This program inputs a 128-bit block of text and a 128-bit key, and encrypts or decrypts the text using the AES algorithm.

## Program Arguments

| Argument | Description                                                                                               |
|----------|-----------------------------------------------------------------------------------------------------------|
| `-v`     | Use verbose output.                                                                                       |
| `-e`     | (Default) Run in encrypt mode.                                                                            |
| `-d`     | Run in decrypt mode.                                                                                      |
| `text`   | (Positional) Input text in hexadecimal format; either plaintext or ciphertext depending on other options. |
| `key`    | (Positional) Encryption/decryption key in hexadecimal format.                                             |

**Note:** You must provide options before positional arguments.

## Build Information

To build the program, use the included Makefile by running `make`.

## Example

We can verify the program correctness by encrypting some plaintext, decryping the resultant ciphertext, and ensuring the plaintexts match.

Encrypting some plaintext:
```
$ 
```

Decrypting the ciphertext:
```
$ 
```

The plaintexts match, which is a good sign that the program works!

## Sources

The following sources were crucial for building this project:
- Cryptography and Network Security: Principles and Practice 7e by William Stallings
- [The DES Algorithm Illustrated](https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm)
- [JavaScript DES Example](https://people.duke.edu/%7Etkb13/courses/ncsu-csc405-2015fa/RESOURCES/JS-DES.shtml)