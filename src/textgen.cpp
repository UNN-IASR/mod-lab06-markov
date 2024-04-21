// Copyright 2024 Kapochkin Mikhail
#include "textgen.h"
#include <sstream>
#include <random>

void TextGen::set(std::map<prefix, std::vector<std::string>> states) {
    statetab = states;
}
std::map<prefix, std::vector<std::string>> TextGen::get() {
    return statetab;
}
void TextGen::CreateStatetabPrefixes(const std::string& inpstr, int prefnum) {
    std::istringstream input_text(inpstr);
    prefix current_prefix;
    std::string word;
    for (int i = 0; i < prefnum; i++) {
        input_text >> word;
        current_prefix.push_back(word);
    }

    first_prefix = current_prefix;
    while (input_text >> word) {
        statetab[current_prefix].push_back(word);
        current_prefix.push_back(word);
        current_prefix.pop_front();
    }
}
std::string TextGen::GenerateText(int generation_seed, int MAXGEN) {
    std::mt19937 mt(time(nullptr));
    int randomNumber;
    std::string text_for_output;
    prefix curpref = first_prefix;
    std::string new_prefix;
    for (auto prefIt = curpref.begin(); prefIt != curpref.end(); prefIt++) {
        text_for_output += *prefIt + " ";
        MAXGEN--;
    }
    for (int i = 0; i < MAXGEN; i++) {
        if (statetab.find(curpref) == statetab.end()) break;
        randomNumber = mt() % statetab[curpref].size();
        new_prefix = statetab[curpref][randomNumber];
        text_for_output += new_prefix + " ";
        curpref.push_back(new_prefix);
        curpref.pop_front();
    }
    return text_for_output;
}
