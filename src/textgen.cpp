// Copyright 2024 Vyacheslav Bolshakov
#include "../include/textgen.h"

void MGenerator::read_file(const char* filename, int n) {
    std::ifstream file(filename);
    std::string word;
    std::string text = "";
    while (file >> word) {
        text += word + " ";
    }
    read_text(text, n);
}

void MGenerator::read_text(std::string text, int n) {
    std::istringstream stream(text);
    std::string word;
    prefix pref;
    for (int i = 0; i < n; i++) {
        stream >> word;
        pref.push_back(word);
    }
    while (stream >> word) {
        prefixes.push_back(pref);
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }
}

std::string MGenerator::generate_text(int nwords) {
    std::random_device rnd;
    std::mt19937 mt19(rnd());
    std::uniform_int_distribution<> distr(0, INT_MAX);
    prefix pref = prefixes[distr(mt19) % prefixes.size()];
    std::string res = "";
    for (int i = 0; i < pref.size(); i++) {
        res += pref[i] + " ";
    }
    for (int i = 0; i < nwords-pref.size(); i++) {
        std::vector<std::string> suf = statetab[pref];
        if (suf.empty()) {
            break;
        }
        std::string w = suf[distr(mt19) % suf.size()];
        pref.pop_front();
        pref.push_back(w);
        res += w + " ";
    }
    return res;
}
