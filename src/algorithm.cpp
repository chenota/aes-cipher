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

void keyG(uint8_t word[4], size_t round) {
    // Shift columns of word
    uint8_t temp = word[0];
    for(size_t i = 0; i < 3; i++) word[i] = word[i + 1];
    word[3] = temp;
    // Perform s-box on each byte
    for(size_t i = 0; i < 4; i++) word[i] = FORWARD_S_BOX[word[i] >> 4][word[i] & 0xF];
    // Add round constant to leftmost byte
    word[0] = word[0] ^ ROUND_CONSTANT[round];
}

void aes(uint8_t text[4][4], uint8_t key[4][4], uint8_t result[4][4], bool encrypt, bool verbose) {
    // Verbose print
    if(verbose) {
        std::cout << "Round 0" << std::endl;
        std::cout << " Key: ";
        for(size_t j = 0; j < 4; j++) for(size_t k = 0; k < 4; k++) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) key[j][k] << (j == 3 && k == 3 ? '\n' : ' ');
        std::cout << " Add RoundKey: ";
        addRoundKey(text, key);
        for(size_t j = 0; j < 4; j++) for(size_t k = 0; k < 4; k++) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) text[j][k] << (j == 3 && k == 3 ? '\n' : ' ');
    }
    // Key storage
    uint8_t keys[48][4];
    // First four items in keys array are original key
    for(size_t i = 0; i < 4; i++) for(size_t j = 0; j < 4; j++) keys[i][j] = key[i][j];
    // Generate ten keys
    for(size_t i = 1; i < 12; i++) {
        // Base address for this word
        size_t base = i * 4;
        // Copy last word
        uint8_t lastCopy[4];
        for(size_t j = 0; j < 4; j++) lastCopy[j] = keys[base - 1][j];
        // Perform G on lastCopy
        keyG(lastCopy, i - 1);
        // XOR w/ previous base word
        for(size_t j = 0; j < 4; j++) keys[base][j] = lastCopy[j] ^ keys[base - 4][j];
        // XOR rest
        for(size_t j = 1; j < 4; j++) for(size_t k = 0; k < 4; k++) keys[base + j][k] = keys[base + j - 1][k] ^ keys[base + j - 4][k];
    }
    // Ten rounds
    for(size_t i = 0; i < 10; i++) {
        // Key
        uint8_t roundKey[4][4];
        // Fill round key
        for(size_t j = 0; j < 4; j++) for(size_t k = 0; k < 4; k++) roundKey[j][k] = keys[((i + 1) * 4) + j][k];
        // Verbose print
        if(verbose) {
            std::cout << "Round " << std::dec << i + 1 << std::endl;
            std::cout << " Key: ";
            for(size_t j = 0; j < 4; j++) for(size_t k = 0; k < 4; k++) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) roundKey[j][k] << (j == 3 && k == 3 ? '\n' : ' ');
        };
        
    }
}