// Copyright 2024 Danil Volkov

#include <iostream>
#include <fstream>
#include <locale>
#include "../include/textgen.h"

std::string readTextFromFile(const std::string& filename) {
    std::string text;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            text += line + " ";
        }
        text.pop_back();
        file.close();
    }

    return text;
}

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;

    std::locale::global(std::locale(""));

    std::string inputText = readTextFromFile("text.txt");

    MarkovChain markovChain;
    markovChain.train(inputText, NPREF);

    std::string text = markovChain.generate(MAXGEN, 123);
    std::cout << text;
    return 0;
}
