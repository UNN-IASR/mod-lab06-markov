// Copyright 2022 UNN-IASR
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <deque>
#include <vector>
#include <string>
#include "textgen.h"

TextGenerator::TextGenerator(int NPREF, int MAXGEN) {
    this->NPREF = NPREF;
    this->MAXGEN = MAXGEN;
}

void TextGenerator::gatherData(std::string filename) {
    statetab.clear();
    firstPrefix.clear();
    std::ifstream inputFile(filename);
    if (!inputFile) {
        throw std::runtime_error("File not found: " + filename);
    }
    std::string line;
    std::deque<std::string> deq;
    bool prefixSaved = false;
    while (getline(inputFile, line)) {
        std::vector<std::string> words;
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }
        for (const auto& word : words) {
            if (deq.size() < NPREF) {
                deq.push_back(word);
            } else {
                if (!prefixSaved) {
                    firstPrefix = deq;
                    prefixSaved = true;
                }
                statetab[deq].push_back(word);
                deq.pop_front();
                deq.push_back(word);
            }
        }
    }
    inputFile.close();
}

void TextGenerator::generateText(std::ostream& outStream) {
    if (statetab.empty()) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    prefix currentPrefix = firstPrefix;
    for (const auto& word : firstPrefix) {
        outStream << word << ' ';
    }
    for (int i = 0; i < MAXGEN; i++) {
        auto iter = statetab.find(currentPrefix);
        if (iter == statetab.end() || iter->second.empty()) {
            break;
        }
        std::uniform_int_distribution<int> dist(0, iter->second.size() - 1);
        std::string nextWord = iter->second[dist(gen)];
        outStream << nextWord << ' ';
        currentPrefix.pop_front();
        currentPrefix.push_back(nextWord);
    }
}

std::vector<std::string> TextGenerator::getSuffixes(prefix prefx) {
    return statetab[prefx];
}

int TextGenerator::getPrefixesCount() {
    return statetab.size();
}

void TextGenerator::addRecord(prefix prefx, std::string suffix) {
    statetab[prefx].push_back(suffix);
}
