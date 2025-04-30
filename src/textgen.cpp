// Copyright 2022 UNN-IASR
#include <map>
#include <string>
#include <vector>
#include "textgen.h"

TextGeneratorClass::TextGeneratorClass(std::string Filepath) {
    std::vector<std::string> words = readWords(Filepath);
    stateTab = buildStateTab(words);
}

prefix TextGeneratorClass::GetStartPrefix() {
    return start_prefix;
}

void TextGeneratorClass::SetStartPrefix(prefix newStartPrefix) {
    start_prefix = newStartPrefix;
}

std::map < prefix, std::vector<std::string>> TextGeneratorClass::GetStateTab() {
    return stateTab;
}

void TextGeneratorClass::SetStateTab
(std::map < prefix, std::vector<std::string>> newStateTab) {
    stateTab = newStateTab;
}

std::vector<std::string> TextGeneratorClass::readWords(std::string Filepath) {
    std::vector<std::string> words;
    std::string word;
    std::ifstream file(Filepath);
    if (!file) {
        return words;
    }
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

std::map<prefix, std::vector<std::string>>
TextGeneratorClass::buildStateTab(std::vector<std::string> words) {
    std::map<prefix, std::vector<std::string>> newStateTab;
    if (words.size() < NPREF)
        return newStateTab;
    prefix curPrefix(words.begin(), words.begin() + NPREF);
    start_prefix = curPrefix;
    for (int i = NPREF; i < words.size(); ++i) {
        newStateTab[curPrefix].push_back(words[i]);
        curPrefix.pop_front();
        curPrefix.push_back(words[i]);
    }
    end_prefix = curPrefix;
    return newStateTab;
}

std::string TextGeneratorClass::generateText() {
    std::string genText = "";
    if (stateTab.empty())
        return genText;
    prefix curPrefix = start_prefix;
    for (int i = 0; i < curPrefix.size(); ++i) {
        genText += curPrefix[i] + " ";
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int count = NPREF; count < MAXGEN; ++count) {
        if (curPrefix == end_prefix)
            return genText;
        std::string nextWord = chooseNextWord(curPrefix, gen);
        genText += nextWord + " ";
        if (count % 10 == 0)
            genText += "\n";
        curPrefix.pop_front();
        curPrefix.push_back(nextWord);
    }
    return genText;
}

std::string TextGeneratorClass::chooseNextWord(prefix pref, std::mt19937 gen) {
    auto it = stateTab.find(pref);
    if (it->second.empty())
        return "";
    std::vector<std::string> suffixes = it->second;
    std::uniform_int_distribution<> dis(0, suffixes.size() - 1);
    return suffixes[dis(gen)];
}
