// Copyright 2022 UNN-IASR
#include <fstream>
#include <iostream>
#include <string>

#include "textgen.h"

int main() {
    MarkovChain generator("data.txt", 2);
    std::ofstream output("gen.txt");
    std::string generatedText = generator.generate(1000);
    output << generatedText;
    std::cout << generatedText;
}
