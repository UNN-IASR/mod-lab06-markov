// Copyright 2024 Vladislav Labutin

#include "textgen.h"

void markov::train(const std::string& filename, int npref) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "can't open file" << std::endl;
    }
    prefix pref;
    std::string word;
    while (file >> word) {
        if (pref.size() < npref) {
            pref.push_back(word);
            continue;
        }
        table[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }
    file.close();
}

std::string markov::generate(int len, bool randfirst) {
    std::string result = "";
    std::mt19937 mt(static_cast<unsigned int>(time(NULL)));
    auto it = table.begin();
    if (randfirst) {
        std::uniform_int_distribution<> udist(0, table.size()-1);
        std::advance(it, udist(mt));
    }
    prefix pref = it->first;
    for (int i = 0; i < pref.size(); i++) {
        result += pref[i] + " ";
    }
    for (int i = 0; i < len-pref.size(); i++) {
        suffixes suffs = table[pref];
        if (suffs.empty()) break;
        std::uniform_int_distribution<> udist(0, suffs.size()-1);
        std::string word = suffs[udist(mt)];
        result += word + " ";
        pref.pop_front();
        pref.push_back(word);
    }
    return result;
}
