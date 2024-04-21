// Copyright [year] <Copyright Owner>
#include "textgen.h"
#include <random>
#include <sstream>

void Text_Gen::set(std::map<prefix, std::vector<std::string>> states) {
    states = states;
}

std::map<prefix, std::vector<std::string>> Text_Gen::get() {
    return statetab;
}

void Text_Gen::Prefixes(const std::string& str, int num) {
    std::istringstream input_text(str);
    prefix current_prefix;
    std::string word;
    for (int i = 0; i < num; i++) {
        input_text >> word;
        current_prefix.push_back(word);
    }

    f_prefix = current_prefix;
    while (input_text >> word) {
        statetab[current_prefix].push_back(word);
        current_prefix.push_back(word);
        current_prefix.pop_front();
    }
}

std::string Text_Gen::Text(int generation_seed, int MAXGEN) {
    std::mt19937 mt(time(nullptr));
    int randomNumber;
    std::string text;
    prefix curpref = f_prefix;
    std::string new_prefix;
    for (auto prefIt = curpref.begin(); prefIt != curpref.end(); prefIt++) {
        text += *prefIt + " ";
        MAXGEN--;
    }
    for (int i = 0; i < MAXGEN; i++) {
        if (statetab.find(curpref) == statetab.end()) break;
        randomNumber = mt() % statetab[curpref].size();
        new_prefix = statetab[curpref][randomNumber];
        text += new_prefix + " ";
        curpref.push_back(new_prefix);
        curpref.pop_front();
    }
    return text;
}
