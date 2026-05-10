// Copyright 2021 GHA Test Team
#include <random>
#include <ctime>
#include <algorithm>
#include "textgen.h"

const int TextGen::NPREF;

void TextGen::clear() {
    statetab.clear();
}

void TextGen::readText(std::istream& in) {
    statetab.clear();
    prefix pref;
    std::string word;

    for (int i = 0; i < NPREF; ++i) {
        if (in >> word) {
            pref.push_back(word);
        } else {
            return;
        }
    }

    while (in >> word) {
        std::vector<std::string>& suffixes = statetab[pref];

        bool found = false;
        for (size_t i = 0; i < suffixes.size(); ++i) {
            if (suffixes[i] == word) {
                found = true;
                break;
            }
        }

        if (!found) {
            suffixes.push_back(word);
        }

        pref.pop_front();
        pref.push_back(word);
    }
}

std::string TextGen::generate(int nwords) {
    if (statetab.empty()) return "";

    std::string result = "";
    std::mt19937 gen(static_cast<unsigned int>(std::time(0)));

    std::map<prefix, std::vector<std::string>>::iterator it = statetab.begin();
    std::advance(it, 
        std::uniform_int_distribution<>(0, statetab.size() - 1)(gen));
    prefix pref = it->first;

    for (std::deque<std::string>::const_iterator s = pref.begin(); 
    s != pref.end(); ++s) {
        if (!result.empty()) result += " ";
        result += *s;
    }

    int words_generated = NPREF;
    int max_attempts = nwords * 10; 
    int attempts = 0;

    while (words_generated < nwords && attempts < max_attempts) {
        attempts++;

        if (statetab.find(pref) == statetab.end() || statetab[pref].empty()) {
            std::map<prefix, std::vector<std::string>>::iterator random_it = statetab.begin();
            std::advance(random_it, std::uniform_int_distribution<>(0, statetab.size() - 1)(gen));
            pref = random_it->first;
            continue;
        }

        std::vector<std::string>& suffixes = statetab[pref];
        std::uniform_int_distribution<> dis(0, suffixes.size() - 1);
        std::string suffix = suffixes[dis(gen)];

        result += " " + suffix;
        words_generated++;

        pref.pop_front();
        pref.push_back(suffix);
    }

    return result;
}
