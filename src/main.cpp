// Copyright 2024 Yuriy Nazarov
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "../include/textgen.h"

std::string ReadTextFromFile(const std::string& filename) {
    std::fstream in(filename);
    std::string result;
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            result += line + " ";
        }
        result.pop_back();
        in.close();
    } else {
        std::cout << "File not found";
    }
    return result;
}
int main() {
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    const int NPREF = 2;
    const int MAXGEN = 1000;
    std::string inputText = ReadTextFromFile("InputText.txt");
    //std::cout << inputText;
    TextGen textGen;
    textGen.TextProcessing(inputText, NPREF);
    std::string text = textGen.GenerateText(MAXGEN);
    std::cout << text;
    return 0;
}
