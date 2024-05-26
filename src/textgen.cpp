// Copyright 2024 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include "../include/textgen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <map>
#include <vector>
#include <random>
#include <ctime>
#include <string>

#endif  // INCLUDE_TEXTGEN_H_

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string>> statetab;

void build(const std::string& filename, int NPREF = 2) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Не удается открыть файл: " << filename << std::endl;
        exit(1);
    }

    std::string word;
    prefix pref;

    while (file >> word) {
        if (pref.size() == NPREF) {
            statetab[pref].push_back(word);
            pref.pop_front();
        }
        pref.push_back(word);
    }
}

std::string generate_text(int max_words) {
    std::string output;
    prefix pref;
    for (auto it = statetab.begin(); it != statetab.end(); ++it) {
        pref = it->first;
        break;
    }

    for (const auto& word : pref) {
        output += word + " ";
    }

    std::default_random_engine
    generator(static_cast<int64_t>(time(0)));
    std::uniform_int_distribution<int> distribution;

    for (int i = 0; i < max_words; ++i) {
        auto suf = statetab[pref];
        if (suf.empty()) break;
        distribution = std::uniform_int_distribution<int>(0, suf.size() - 1);
        std::string next_word = suf[distribution(generator)];
        output += next_word + " ";
        pref.pop_front();
        pref.push_back(next_word);
    }

    return output;
}
