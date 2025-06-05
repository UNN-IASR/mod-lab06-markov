// Copyright 2025 9hkge
#include "textgen.h"
#include <random>

TextGenerator::TextGenerator(int prefix_size, unsigned int random_seed) {
    this->random_seed = random_seed;
    this->prefix_size = prefix_size;
}