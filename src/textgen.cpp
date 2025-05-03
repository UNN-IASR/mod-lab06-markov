// Copyright 2022 UNN-IASR
#include <iostream>
#include <cstdlib>
#include <random>
#include <map>
#include <vector>
#include <string>
#include "textgen.h"


MarkovChain::MarkovChain() {}
MarkovChain::~MarkovChain() {}

void MarkovChain::train(const std::string& text, int prefixLength) {
    if (text.size() < 3) {
        return;
    }
    std::vector<std::string> words = splitText(text);
    startWord.push_back(words[0]);
    startWord.push_back(words[1]);
    for (int i = 0; i < words.size() - prefixLength; i++) {
        Prefix prefix;
        for (int j = 0; j < prefixLength; ++j) {
            prefix.push_back(words[i + j]);
        }
        stateTable[prefix].push_back(words[i + prefixLength]);
    }
}

std::string MarkovChain::generate(int textSize, unsigned int time_generate) {
    Prefix prefix;
    std::string generateText;

    if (stateTable.empty() || startWord.empty()) {
        return "";
    }

    prefix = startWord;

    for (const std::string& elem : prefix) {
        generateText += elem + ' ';
    }

    unsigned int seed = time(0);
    if (time_generate != 0) {
        seed = time_generate;
    }
    std::default_random_engine gen(seed);

    while (generateText.size() < textSize) {
        if (stateTable.find(prefix) != stateTable.end()) {
            const std::vector<std::string>& suffixes = stateTable[prefix];

            if (!suffixes.empty()) {
                std::uniform_int_distribution<> dist(0, suffixes.size() - 1);
                int randomIndex = dist(gen);
                generateText += suffixes[randomIndex] + ' ';
                prefix.pop_front();
                prefix.push_back(suffixes[randomIndex]);
            } else {
                break;
            }
        } else {
            break;
        }
    }

    if (!generateText.empty() && generateText.back() == ' ') {
        generateText.pop_back();
    }

    if (generateText.size() > textSize) {
        generateText = generateText.substr(0, textSize);
    }

    return generateText;
}

void MarkovChain::trainFromStateTable(
    const std::map<Prefix,
    std::vector<std::string>>&newStateTable) {
    stateTable = newStateTable;

    if (!stateTable.empty()) {
        auto item = stateTable.begin();
        startWord = item->first;
    }
}

std::vector<std::string> MarkovChain::splitText(const std::string& text) {
    std::vector<std::string> words;
    char delimiter = ' ';
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= text.size(); i++) {
        if (text[i] == delimiter || i == text.size()) {
            endIndex = i;
            std::string temp;
            temp.append(text, startIndex, endIndex - startIndex);
            words.push_back(temp);
            startIndex = endIndex + 1;
        }
    }

    return words;
}
