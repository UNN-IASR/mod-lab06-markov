// Copyright 2022 UNN-IASR
#include "textgen.h"
#include <fstream>
#include <iostream>

int main() {
    const char* input_file = "book.txt";
    const char* output_file = "gen.txt";

    std::ifstream in(input_file);
    if (!in) {
        std::cerr << "Cannot open input file: " << input_file << std::endl;
        return 1;
    }

    TextGenerator generator(2, 1000); 
    generator.build(in);
    in.close();

    std::ofstream out(output_file);
    if (!out) {
        std::cerr << "Cannot open output file: " << output_file << std::endl;
        return 1;
    }

    generator.generate(out);
    out.close();

    std::cout << "Text generation completed. Result saved to " << output_file << std::endl;
    return 0;
}
