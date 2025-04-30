// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

TextGenerator::TextGenerator(int length) : prefixLength(length) {
    std::srand(std::time(nullptr));
}

void TextGenerator::learnFromText(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open the file: " + filename);

    Prefix prefix;
    std::string word;

    for (int i = 0; i < prefixLength && (file >> word); i++) {
        prefix.push_back(word);
    }

    if (prefix.size() == prefixLength) {
        allPrefixes.push_back(prefix);
    }

    while (file >> word) {
        table[prefix].push_back(word);
        allPrefixes.push_back(prefix);

        prefix.pop_front();
        prefix.push_back(word);
    }
}

void TextGenerator::generateText(int wordCount, const std::string& outputFile) {
    std::ofstream out(outputFile);
    if (!out) throw std::runtime_error("Cannot create a file: " + outputFile);

    if (allPrefixes.empty()) {
        throw std::runtime_error("No data to generate");
    }

    Prefix prefix = allPrefixes[std::rand() % allPrefixes.size()];
    int generated = 0;

    for (const auto& word : prefix) {
        out << word << " ";
        generated++;
    }

    while (generated < wordCount) {
        auto it = table.find(prefix);
        if (it == table.end() || it->second.empty()) {
            prefix = allPrefixes[std::rand() % allPrefixes.size()];
            continue;
        }

        const auto& nextWords = it->second;
        std::string nextWord = nextWords[std::rand() % nextWords.size()];

        out << nextWord << " ";
        generated++;

        prefix.pop_front();
        prefix.push_back(nextWord);

        if (generated % 20 == 0)
            out << "\n";
    }
}
