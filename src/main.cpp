// Copyright 2022 UNN-IASR
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>
#include "textgen.h"

int main() {
    setlocale(LC_ALL, ".65001");

    const std::string input_filename = "data/book.txt";

    std::ifstream inputFile(input_filename);

    std::string word;
    std::vector<std::string> words;
    while (inputFile >> word) {
        words.push_back(word);
    }
    inputFile.close();

    MarkovTextGenerator generator;
    generator.createTable(words);
    std::string genText = generator.generateText();

    const std::string output_filename = "result/gen.txt";
    std::ofstream outputFile(output_filename);

    outputFile << genText;
    outputFile.close();

    return 0;
}
