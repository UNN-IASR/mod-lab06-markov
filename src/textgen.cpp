// Copyright Mimi
#include "textgen.h"
void Markov::OperationStatetab(std::string str) {
    bufPref.pop_front();
    bufPref.push_back(str);
}
void Markov::CreateStatetab(std::vector<std::string> words, int NREF) {
    for (int i = 0; i < NREF; i++) {
        bufPref.push_back(words[i]);
    }
    firstPref = bufPref;
    for (int i = NREF; i < words.size(); i++) {
        statetab[bufPref].push_back(words[i]);
        OperationStatetab(words[i]);
    }
}
std::string Markov::CreateText(int MAXGEN) {
    bufPref = firstPref;
    srand(eeq);
    int rnd;
    std::string result;
    for (int i = 0; i < firstPref.size(); i++) {
        result += firstPref[i] + " ";
    }
    for (int i = 0; i < MAXGEN - firstPref.size(); i++) {
        if (statetab.find(bufPref) == statetab.end()) {
            break;
        }
        rnd = rand_r(&eeq) % statetab[bufPref].size();
        result += statetab[bufPref][rnd] + " ";
        OperationStatetab(statetab[bufPref][rnd]);
    }
    return result;
}
