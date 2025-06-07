// Copyright 2025 AirFox

#include <fstream>
#include <iostream>
#include "../include/textgen.h"

int main() {
    std::ifstream input("../../../../src/text.txt");
    std::ofstream output("../../../../result/gen.txt");

    if (!input) {
        std::cerr << "input file error\n";
        return 1;
    }

    if (!output) {
        std::cerr << "output file error\n";
        return 1;
    }

    Chain chain;
    build(input, chain);
    generate(output, chain);

    return 0;
}
