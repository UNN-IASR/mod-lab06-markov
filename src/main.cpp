// src/main.cpp
#include "textgen.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    try {
        TextGeneratorMarkov generator;
        generator.loadText(INPUT_FILE_PATH);
        generator.generateText(OUTPUT_FILE_PATH);
    } catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }
    
    return 0;
}