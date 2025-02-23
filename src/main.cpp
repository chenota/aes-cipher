#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdint.h>
#include "algorithm.hpp"

int main(int argc, char *argv[]) {
    // Argument parsing
    enum {ENCRYPT, DECRYPT} mode = ENCRYPT;
    enum {REGULAR, VERBOSE} print_mode = REGULAR;
    int c;
    while((c = getopt(argc, argv, "edv")) != -1) {
        switch(c) {
            // -e switches mode to encrypt
            case 'e':
                mode = ENCRYPT;
                break;
            // - d switches mode to decrypt
            case 'd':
                mode = DECRYPT;
                break;
            // -v switches to verbose output
            case 'v':
                print_mode = VERBOSE;
                break;
            // Unknown option error
            default:
                std::cerr << "Unknown option: " << c << std::endl;
                exit(1);
        }
    }
    // Check positional arguments
    if(argc - optind != 2) {
        std::cerr << "Expected positional arguments Text and Key" << std::endl;
        exit(1);
    }
    // Cast text and key to strings
    std::string text_str = argv[optind];
    std::string key_str = argv[optind + 1];
    // Buffers to hold strings for text and key
    char text_buf[32] = { '0' };
    char key_buf[32] = { '0' };
    // Validate length
    if(text_str.length() > 32 || key_str.length() > 32) {
        std::cerr << "Text and Key length must be no more than 32 characters" << std::endl;
        exit(1);
    }
    // Fill buffers
    for(size_t i = 0; i < text_str.length(); i++) text_buf[(32 - text_str.length()) + i] = text_str[i];
    for(size_t i = 0; i < key_str.length(); i++) key_buf[(32 - key_str.length()) + i] = key_str[i];
    // Hexit buffer
    char hexit_buf[3] = "00";
    // Allocate text and key blocks
    uint8_t text[4][4] = { 0 };
    uint8_t key[4][4] = { 0 };
    // Fill blocks
    for(size_t i = 0; i < 16; i++) {
        // Fill hexit buffer (text)
        hexit_buf[0] = text_buf[i * 2];
        hexit_buf[1] = text_buf[(i * 2) + 1];
        // Fill value from hexit buffer
        text[i / 4][i % 4] = strtoul(hexit_buf, NULL, 16);
        // Fill hexit buffer (key)
        hexit_buf[0] = key_buf[i * 2];
        hexit_buf[1] = key_buf[(i * 2) + 1];
        // Fill value from hexit buffer
        key[i / 4][i % 4] = strtoul(hexit_buf, NULL, 16);
    }
    // Result buffer
    uint8_t result[4][4];
    // Run AES algorithm
    aes(text, key, result, mode == ENCRYPT, print_mode == VERBOSE);
    // Print result
    for(size_t i = 0; i < 4; i++) for(size_t j = 0; j < 4; j++) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) result[i][j];
    std::cout << std::endl;
    // Return success
    return 0;
}