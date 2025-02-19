#include "algorithm.hpp"

void subBytes(uint8_t bytes[4][4], uint8_t SBOX[8][8]) {
    // Substitute each byte as per selected s-box
    for(uint8_t i = 0; i < 4; i++) {
        for(uint8_t j = 0; j < 4; j++) {
            bytes[i][j] = SBOX[bytes[i][j] >> 4][bytes[i][j] & 0xF];
        }
    }
}

void shiftRows(uint8_t bytes[4][4]) {
    // Make a copy of the bytes matrix
    uint8_t bytes_copy[4][4];
    std::copy(&bytes[0][0], &bytes[0][0]+16, &bytes_copy[0][0]);
    // Update rows of original matrix
    bytes[0][1] = bytes_copy[1][1];
    bytes[0][2] = bytes_copy[2][2];
    bytes[0][3] = bytes_copy[3][3];

    bytes[1][1] = bytes_copy[2][1];
    bytes[1][2] = bytes_copy[3][2];
    bytes[1][3] = bytes_copy[0][3];

    bytes[2][1] = bytes_copy[3][1];
    bytes[2][2] = bytes_copy[0][2];
    bytes[2][3] = bytes_copy[1][3];

    bytes[3][1] = bytes_copy[0][1];
    bytes[3][2] = bytes_copy[1][2];
    bytes[3][3] = bytes_copy[2][3];
}

uint8_t fastMultiply(uint8_t x, uint8_t n) {
    // Base case: If multiplying by n=0 (x^0), return x
    if(n == 0) return x;
    // Recursive case
    uint8_t x_new = fastMultiply(x, n-1);
    // Check if b7 is zero
    if(x_new & 0x80 == 0) {
        return x_new < 1;
    } else {
        return (x_new < 1) ^ 0x1B;
    }
}

void mixColumns(uint8_t bytes[4][4]) {
    // For each of the four columns...
    for(uint8_t i = 0; i < 4; i++) {
        bytes[i][0] = fastMultiply(bytes[i][0], 2) ^ fastMultiply(bytes[i][1], 3) ^ fastMultiply(bytes[i][2], 1) ^ fastMultiply(bytes[i][3], 1);
        bytes[i][1] = fastMultiply(bytes[i][0], 1) ^ fastMultiply(bytes[i][1], 2) ^ fastMultiply(bytes[i][2], 3) ^ fastMultiply(bytes[i][3], 1);
        bytes[i][2] = fastMultiply(bytes[i][0], 1) ^ fastMultiply(bytes[i][1], 1) ^ fastMultiply(bytes[i][2], 2) ^ fastMultiply(bytes[i][3], 3);
        bytes[i][3] = fastMultiply(bytes[i][0], 3) ^ fastMultiply(bytes[i][1], 1) ^ fastMultiply(bytes[i][2], 1) ^ fastMultiply(bytes[i][3], 2);
    }
}

void addRoundKey(uint8_t bytes[4][4], uint8_t key[4][4]) {
    // XOR each text value with key value
    for(uint8_t i = 0; i < 4; i++) {
        for(uint8_t j = 0; j < 4; j++) {
            bytes[i][j] ^= key[i][j];
        }
    }
}

void aes(uint8_t text[4][4], uint8_t key[4][4], bool verbose) {

}