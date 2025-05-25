// Copyright 2022 UNN-IASR
#include "textgen.h"

#include <iostream>
#include <string>

const int NPREF = 2;      // the number of words in the prefix
const int MAXGEN = 1000;  // the amount of text in the output

void TextGenerator::analyzeText(const std::string& filepath) {
    std::ifstream file(filepath);
    prefix pref;
    if (!file) {
        std::cerr << "Error when trying to open a file "
            << filepath << std::endl;
    }
    for (int i = 0; i < prefixLen_; i++) {
        std::string w;
        file >> w;
        pref.push_back(w);
    }
    initPref_ = pref;
    std::string word;
    while (file >> word) {
        statetab_[pref].push_back(word);
        pref.push_back(word);
        pref.pop_front();
    }
    endPref_ = pref;
}

std::string TextGenerator::genText(int textLen = MAXGEN) {
    std::string text = "";
    prefix pref = initPref_;
    for (int i = 0; i < pref.size(); i++) {
        text += pref[i] + " ";
    }
    for (int i = 0; i < textLen - pref.size(); i++) {
        if (pref == endPref_) return text;
        std::string word = genSuffix(pref);
        text += word + " ";
        if (i % 20 == 0) text += "\n";
        pref.push_back(word);
        pref.pop_front();
    }
    return text;
}

std::string TextGenerator::genSuffix(const prefix& pref) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, statetab_[pref].size() - 1);
    return statetab_[pref][distribution(generator)];
}

void TextGenerator::addTransition(
    const prefix& pref,
    const std::string& word) {
    if (initPref_.size() == 0) initPref_ = pref;
    statetab_[pref].push_back(word);
    endPref_ = { pref[pref.size() - 1], word };
}
