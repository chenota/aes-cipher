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
$ ./aes.out -e 54776F204F6E65204E696E652054776F 5468617473206D79204B756E67204675
29c3505f571420f6402299b31a02d73a
```

Decrypting the ciphertext:
```
$ ./aes.out -d 29c3505f571420f6402299b31a02d73a 5468617473206D79204B756E67204675
54776f204f6e65204e696e652054776f
```

The plaintexts match, which is a good sign that the program works!

## Sources

The following sources were crucial for building this project:
- Cryptography and Network Security: Principles and Practice 7e by William Stallings
- [AES Example](https://www.kavaliro.com/wp-content/uploads/2014/03/AES.pdf)
- [Advanced Encryption Standard](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)