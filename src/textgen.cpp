// Copyright 2024 RuzKate

#include <iostream>
#include <cstdlib>
#include <random>
#include "../include/textgen.h"

void MarkovGenerator::CreateTable(std::string text, int count) {
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

    startWord.push_back(words[0]);
    startWord.push_back(words[1]);

    for (int i = 0; i < words.size() - count; i++) {
        Prefix prefix;
        for (int j = 0; j < count; ++j) {
            prefix.push_back(words[i + j]);
        }
        statetab[prefix].push_back(words[i + count]);
    }
}

std::string MarkovGenerator::Generate(int count, unsigned int time_generate) {
    Prefix prefix;
    std::string genText;

    prefix = startWord;

    for (const std::string& elem : prefix) {
        genText += elem + ' ';
    }

    unsigned int seed = time(0);
    if (time_generate != 0) {
        seed = time_generate;
    }
    std::default_random_engine gen(seed);

    while (genText.size() < count) {
        if (statetab.find(prefix) != statetab.end()) {
            const std::vector<std::string>& suffixes = statetab[prefix];

            if (!suffixes.empty()) {
                std::uniform_int_distribution<> dist(0, suffixes.size() - 1);
                int randomIndex = dist(gen);
                genText += suffixes[randomIndex] + ' ';
                prefix.pop_front();
                prefix.push_back(suffixes[randomIndex]);
            } else {
                break;
            }
        } else {
            break;
        }
    }

    if (!genText.empty() && genText.back() == ' ') {
        genText.pop_back();
    }

    if (genText.size() > count) {
        genText = genText.substr(0, count);
    }

    return genText;
}

std::map<Prefix, std::vector<std::string>> MarkovGenerator::getTab() {
    return statetab;
}

void MarkovGenerator::trainFromStateTable(
    const std::map<Prefix,
    std::vector<std::string>>&newStateTable) {
    statetab = newStateTable;

    if (!statetab.empty()) {
        auto item = statetab.begin();
        startWord = item->first;
    }
}
