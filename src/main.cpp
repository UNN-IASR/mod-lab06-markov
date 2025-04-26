// Copyright 2022 UNN-IASR
#include <fstream>
#include <iostream>
#include "textgen.h"


int main() {
    try {
        TextGenerator generator_markova;
        generator_markova.build_state_table(INPUT_FILE_PATH, generator_markova.NPREF);
        generator_markova.generate_text(OUTPUT_FILE_PATH, generator_markova.MAXGEN);
        std::cout << "Text generation completed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
