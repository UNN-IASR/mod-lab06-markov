// Copyright 2024 Kokorin Alexandr

#include "textgen.h"
#include <time.h>
#include <random>
#include <deque>
#include <map>
#include <vector>

textgen::textgen(const std::string& text, const int NREF) {
    std::vector<std::string> table;
    int left = 0;
    for (int i = 0; i <= text.size(); i++) {
        if (text[i] == ' ' || i == text.size()) {
            std::string word;
            word.append(text, left, i - left);
            table.push_back(word);
            left = i + 1;
        }
    }
    for (int i = 0; i < NREF; i++) {
        prefix.push_back(table[i]);
    }
    for (int i = 0; i < table.size() - NREF; i++) {
        Prefix pref;
        for (int j = 0; j < NREF; j++) {
            pref.push_back(table[i + j]);
        }
        stateTable[pref].push_back(table[i + NREF]);
    }
}

textgen::textgen(const std::map<Prefix, std::vector<std::string>>& stateTable) {
    textgen::stateTable = stateTable;
    if (!stateTable.empty()) {
        auto item = stateTable.begin();
        prefix = item->first;
    }
}

std::string textgen::generate(const int MAXGEN) {
    std::string text;
    std::default_random_engine gen(time(0));
    for (int i = 0; i < prefix.size(); i++) {
        text += prefix[i];
        text += ' ';
    }
    for (int i = 0; i < MAXGEN &&
        stateTable.find(prefix) != stateTable.end(); i++) {
        std::vector<std::string> suffix = stateTable[prefix];
        if (!suffix.empty()) {
            std::uniform_int_distribution<> dist(0, suffix.size() - 1);
            int randomIndex = dist(gen);
            text += suffix[randomIndex] + ' ';
            prefix.pop_front();
            prefix.push_back(suffix[randomIndex]);
        } else {
            break;
        }
    }

    return text;
}
