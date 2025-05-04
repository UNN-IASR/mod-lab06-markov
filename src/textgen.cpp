// Copyright 2022 UNN-IASR
#include "textgen.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

TextGenerator::TextGenerator() {}

std::vector<std::string> TextGenerator::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    return words;
}

void TextGenerator::createTable(const std::string& filename, int prefLenght) {
    this->prefLenght = prefLenght;
    std::vector<std::string> words = readFile(filename);
    if (words.size() < static_cast<size_t>(prefLenght + 1)) {
        throw std::runtime_error(
            "Input text is too short for the given prefix size");
    }

    table.clear();
    for (int i = 0; i < prefLenght; i++) firstPrefix.push_back(words[i]);

    for (int i = 0; i < words.size() - prefLenght; i++) {
        prefix pref;
        for (int j = 0; j < prefLenght; j++) pref.push_back(words[i + j]);
        table[pref].push_back(words[i + prefLenght]);
    }
}

void TextGenerator::generateText(int maxCount, const std::string& filename) {
    prefix pref = firstPrefix;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::string outText = pref[0];
    for (int i = 1; i < prefLenght; i++) outText += " " + pref[i];

    for (int i = 0; i < maxCount; i++) {
        auto suff = table[pref];
        if (suff.empty()) break;
        std::uniform_int_distribution<std::mt19937::result_type> dist(
            0, suff.size() - 1);
        std::string nextWord = suff[dist(rng)];

        outText += " " + nextWord;
        pref.pop_front();
        pref.push_back(nextWord);
    }

    std::ofstream outStream(filename);
    outStream << outText;
    std::cout << "Text generation completed. Result saved to " << filename
                << std::endl;
}
