// Copyright 2024

#include <sstream>
#include <string>

#include "../include/textgen.h"

void Generator::Train(const std::string& text, int prefixSize) {
    std::istringstream iss(text);
    Prefix prefix;
    std::string word;
    for (int i = 0; i < prefixSize; i++) {
        iss >> word;
        prefix.push_back(word);
    }
    while (iss >> word) {
        chain[prefix].push_back(word);
        prefix.pop_front();
        prefix.push_back(word);
    }
}

std::string Generator::Generate(int length, unsigned int seed) {
    int index = rand_r(&seed) % chain.size();
    auto chain_it = chain.begin();
    std::advance(chain_it, index);
    Prefix prefix = chain_it->first;

    std::string result;

    for (auto it = prefix.begin(); it != prefix.end(); ++it)
        result += *it + " ";

    for (int i = 0; i < length; i++) {
        std::vector<std::string> suffix = chain[prefix];
        if (suffix.empty()) break;
        int next_index = rand_r(&seed) % suffix.size();
        std::string next = suffix[next_index];
        result += next + " ";
        prefix.pop_front();
        prefix.push_back(next);
    }
    return result;
}

void Generator::setChain(std::map<Prefix, std::vector<std::string>> _chain) {
    chain = _chain;
}

std::map<Prefix, std::vector<std::string>> Generator::getChain() {
    return chain;
}
