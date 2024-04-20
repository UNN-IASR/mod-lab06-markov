// Copyright 2022 UNN-IASR
#include "textgen.h"
void MarkovChain::Tab(std::vector<std::string> words, int NREF) {
    prefix pref;
    int global = 0;
    for (int i = 0; i < NREF; i++) {
        pref.push_back(words[global]);
        global++;
    }
    fpref = pref;
    while (global < words.size()) {
        statetab[pref].push_back(words[global]);
        pref.pop_front();
        pref.push_back(words[global]);
        global++;
    }
}
std::string MarkovChain::CreateText(int MAXGEN, unsigned int seed) {
    srand(seed);
    int randomValue;
    std::string textOut;
    std::string suffix;
    prefix pref = fpref;
    for (int i = 0; i < fpref.size(); i++) {
        textOut += fpref[i] + " ";
        MAXGEN--;
        }
    for (int i = 0; i < MAXGEN; i++) {
        if (statetab.find(pref) == statetab.end()) break;
        randomValue = rand_r(&seed) % statetab[pref].size();
        suffix = statetab[pref][randomValue];
        textOut += suffix + " ";
        pref.pop_front();
        pref.push_back(suffix);
}
    return textOut;
}
