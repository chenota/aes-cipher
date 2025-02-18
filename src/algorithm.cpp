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
    bytes[1][0] = bytes_copy[1][1];
    bytes[2][0] = bytes_copy[2][2];
    bytes[3][0] = bytes_copy[3][3];

    bytes[1][1] = bytes_copy[1][2];
    bytes[2][1] = bytes_copy[2][3];
    bytes[3][1] = bytes_copy[3][0];

    bytes[1][2] = bytes_copy[1][3];
    bytes[2][2] = bytes_copy[2][0];
    bytes[3][2] = bytes_copy[3][1];

    bytes[1][3] = bytes_copy[1][0];
    bytes[2][3] = bytes_copy[2][1];
    bytes[3][3] = bytes_copy[3][2];
}