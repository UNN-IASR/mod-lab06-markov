//Copyright 2024 UNN-IASR
#include <iostream>
#include <cstdlib>
#include <random>
#include "textgen.h"

TextGen::TextGen() {}

void TextGen::create_tab(const std::string& text, int number) {
    std::vector<std::string> word;
    char share = ' ';
    int begin = 0;
    int final = 0;
    std::string str;

    for (int i = 0; i <= text.size(); i++) {
        if (text[i] == share || i == text.size()) {
            final = i;
            str.append(text, begin, final - begin);
            word.push_back(str);
            begin = final + 1;
        }
    }

    first.push_back(word[0]);
    first.push_back(word[1]);
    for (int i = 0; i < word.size() - number; i++) {
        prefix pref;
        for (int j = 0; j < number; j++) {
            pref.push_back(word[i + j]);
        }
        tab_state[pref].push_back(word[i + number]);
    }
}

std::string TextGen::generate(int number, unsigned int time_num) {
    prefix pre;
    std::string intel;
    pre = first;

    for (const std::string& elem : pre) {
        intel += elem + ' ';
    }

    unsigned int p = time(0);
    if (time_num != 0) {
        p = time_num;
    }
    std::default_random_engine gener(p);

    while (intel.size() < number) {
        if (tab_state.find(pre) != tab_state.end()) {
            const std::vector<std::string>& suf = tab_state[pre];

            if (!suf.empty()) {
                std::uniform_int_distribution<> dist(0, suf.size() - 1);
                int index = dist(gener);
                intel += suf[index] + ' ';
                pre.pop_front();
                pre.push_back(suf[index]);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (intel.size() > number) {
        intel = intel.substr(0, number);
    }
    return intel;
}

void TextGen::StateTable(
    const std::map<prefix,
    std::vector<std::string>>&newstatetab) {
    tab_state = newstatetab;

    if (!tab_state.empty()) {
        auto item = tab_state.begin();
        first = item -> first;
    }
}
