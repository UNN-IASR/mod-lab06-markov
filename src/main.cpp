// Copyright 2022 UNN-IASR
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include "textgen.h"

std::string readTextFromFile(const std::string& filename) {
    std::string text;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            text += line + " ";
        }
        if (!text.empty()) {
            text.pop_back();
        }
        file.close();
    }

    return text;
}

void saveTextToFile(const std::string& filename, const std::string& content) {
    #ifdef _WIN32
        system("mkdir ..\\..\\result 2>nul");
    #endif

    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
    } else {
        std::cerr << "Unable to open file for writing: "
            << filename << std::endl;
    }
}

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;

    std::locale::global(std::locale(""));

    std::string inputText = readTextFromFile("../../src/text.txt");

    MarkovChain markovChain;
    markovChain.train(inputText, NPREF);

    std::string text = markovChain.generate(MAXGEN, 123);
    saveTextToFile("../../result/gen.txt", text);
    return 0;
}
