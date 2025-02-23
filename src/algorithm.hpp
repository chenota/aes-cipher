#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <stdint.h>
#include "data.hpp"
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iomanip>

void aes(uint8_t text[4][4], uint8_t key[4][4], uint8_t result[4][4], bool encrypt, bool verbose);

#endif