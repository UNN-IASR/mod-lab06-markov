// Copyright 2025 AirFox

#include "../include/textgen.h"


void build(std::ifstream& in, Chain& chain) {
    Prefix prefix;
    for (int i = 0; i < prefixSize; ++i)
        prefix.push_back("");

    std::string word;
    while (in >> word) {
        chain[prefix].push_back(word);

        prefix.pop_front(); 
        prefix.push_back(word);
    }
}

void generate(std::ofstream& out, Chain& chain) {
    Prefix prefix;
    for (int i = 0; i < prefixSize; ++i)
        prefix.push_back(""); 

    for (int i = 0; i < maxGenWords; ++i) {
        auto it = chain.find(prefix);
        if (it == chain.end()) break;

        std::vector<std::string>& suffixes = it->second;
        if (suffixes.empty()) break;

        int index = rand() % suffixes.size();
        std::string next = suffixes[index];

        out << next << " ";

        prefix.pop_front();
        prefix.push_back(next);
    }
}
