// Copyright 2025 AirFox

#include "../include/textgen.h"
#include <cstdlib>
#include <vector>
#include <string>

void build(std::ifstream& in, Chain& chain) {
    Prefix prefix;

    for (int i = 0; i < prefixSize; ++i) {
        prefix.push_back("");
    }

    std::string word;
    while (in >> word) {
        chain[prefix].push_back(word);
        prefix.pop_front();
        prefix.push_back(word);
    }
}

void generate(std::ofstream& out, Chain& chain) {
    Prefix prefix;

    for (int i = 0; i < prefixSize; ++i) {
        prefix.push_back("");
    }

    for (int i = 0; i < maxGenWords; ++i) {
        auto it = chain.find(prefix);
        if (it == chain.end() || it->second.empty()) {
            break;
        }

        const auto& suffixes = it->second;
        const std::string& next = suffixes[std::rand() % suffixes.size()];
        out << next << " ";

        prefix.pop_front();
        prefix.push_back(next);
    }

    out << "\n";
}
