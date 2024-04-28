// Copyright 2024 Goncharova Anna
#include "textgen.h"
#include <time.h>
#include <random>
#include <deque>
#include <vector>

void Generator::creating_statetab(const std::string& string, int size) {
    std::istringstream text(string);
    prefix prefix;
    std::string word;
    for (int i = 0; i < size; i++) {
        text >> word;
        prefix.push_back(word);
    }
    _prefix = prefix;
    while (text >> word) {
        statetab[prefix].push_back(word);
        prefix.pop_front();
        prefix.push_back(word);
    }
}
std::string Generator::Text_generator(int maxgen, int time) {
    std::string  generated_text;
    std::default_random_engine generator(time);
    for (int i = 0; i < _prefix.size(); i++) {
        generated_text += _prefix[i] + ' ';
    }
    for (int i = 0; i < maxgen &&
        statetab.find(_prefix) != statetab.end(); i++) {
        std::vector<std::string> suffix = statetab[_prefix];
        if (!suffix.empty()) {
            std::uniform_int_distribution<> dist(0, suffix.size() - 1);
            int randomIndex = dist(generator);
            generated_text += suffix[randomIndex] + ' ';
            _prefix.pop_front();
            _prefix.push_back(suffix[randomIndex]);
        } else {
            break;
        }
    }
    return generated_text;
}

void Generator::trainFromStateTable(
    const std::map<prefix,
    std::vector<std::string>>& newStateTable) {
    statetab = newStateTable;

    if (!statetab.empty()) {
        auto item = statetab.begin();
        _prefix = item->first;
    }
}
