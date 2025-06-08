// Copyright 2024

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../include/textgen.h"

int main() {
    std::ifstream file("input.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    Generator generator;
    generator.Train(text, 2);
    std::string generated_text = generator.Generate(1000);
    std::cout << generated_text;
}
