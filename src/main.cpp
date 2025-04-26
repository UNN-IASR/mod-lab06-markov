// Copyright 2022 UNN-IASR
#include "textgen.h"
#include <fstream>
#include <iostream>


int main() {
    try {
        TextGenerator generator;  
        generator.build_state_table(INPUT_FILE_PATH);
        generator.generate_text(OUTPUT_FILE_PATH);
        std::cout << "Text generation completed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}