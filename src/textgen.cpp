// Copyright 2024 Yuriy Nazarov
#include <random>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "textgen.h"

TextGen::TextGen() {}

TextGen::~TextGen() {}

std::vector<std::string> TextGen::splitText(const std::string& text) {
    char delimiters[6] = { ' ', '\t', '\n', '\r', '\f', '\v' };
    std::vector<std::string> words;
    std::string curWord;
    for (char symbol : text) {
        if (std::find(delimiters, delimiters + 6, symbol) ==
        std::end(delimiters)) {
            curWord += symbol;
        } else {
            if (!curWord.empty()) {
                words.push_back(curWord);
                curWord.clear();
            }
        }
    }
    if (!curWord.empty()) {
        words.push_back(curWord);
    }
    return words;
}

void TextGen::TextProcessing(const std::string& text, int prefixLength) {
    std::vector<std::string> words = splitText(text);
    if (words.size() < 3) {
        return;
    }
    Prefix curPrefix;
    for (int i = 0; i < prefixLength; i++) {
        curPrefix.push_back(words[i]);
        startPrefix.push_back(words[i]);
    }
    for (int i = prefixLength; i < words.size(); i++) {
        statetab[curPrefix].push_back(words[i]);
        curPrefix.push_back(words[i]);
        curPrefix.pop_front();
    }
}

std::string TextGen::GenerateText(int maxSize) {
    Prefix curPrefix = startPrefix;
    std::string curWord = "";
    std::string text;
    if (statetab.empty() || startPrefix.empty()) {
        return "";
    }
    for (std::string word : curPrefix) {
        text += word + " ";
    }

    std::mt19937 gen;
    gen.seed(std::time(nullptr));

    unsigned int randomIndex = 0;
    while (text.size() < maxSize) {
        if (statetab.find(curPrefix) != statetab.end()) {
            if (!statetab[curPrefix].empty()) {
                randomIndex = gen() % statetab[curPrefix].size();
                curWord = statetab[curPrefix][randomIndex];
                text += curWord + " ";
                curPrefix.push_back(curWord);
                curPrefix.pop_front();
            } else {
                break;
            }
        } else {
            break;
        }
    }
    return text;
}
