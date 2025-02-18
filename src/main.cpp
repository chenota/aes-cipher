#include <unistd.h>
#include <iostream>
#include <string>
#include <stdint.h>

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
    // Validate length
    if(strnlen(argv[optind], 33) > 32 || strnlen(argv[optind + 1], 33) > 32) {
        std::cerr << "Text and Key length must be no more than 32 characters" << std::endl;
        exit(1);
    }
    // Allocate text and key blocks
    uint64_t text = 0;
    uint64_t key = 0;
    // Fill blocks
    text = strtoull(argv[optind], NULL, 16);
    key = strtoull(argv[optind + 1], NULL, 16);
    // Exit success
    return 0;
}