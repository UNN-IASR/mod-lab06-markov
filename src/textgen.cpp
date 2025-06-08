// src/textgen.cpp
// Copyright 2025 ArriVeder4i
#include "textgen.h"

#include <deque>    // for std::deque
#include <vector>   // for std::vector
#include <string>   // for std::string
#include <cstdlib>  // for std::rand
#include <iterator> // for std::advance

void build_prefix_map(std::istream& in,
                      statetab_t& statetab,
                      int npref) {
    std::deque<std::string> pref;
    std::string word;
    for (int i = 0; i < npref; ++i) {
        if (!(in >> word)) return;
        pref.push_back(word);
    }
    while (in >> word) {
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }
}

std::vector<std::string> generate_text(
    const statetab_t& statetab,
    int npref,
    int maxgen) {
    std::vector<std::string> output;
    if (statetab.empty() || maxgen < 0) return output;

    auto it_start = statetab.begin();
    prefix pref = it_start->first;
    for (const auto& w : pref) {
        output.push_back(w);
    }
    for (int i = 0; i < maxgen; ++i) {
        auto it = statetab.find(pref);
        if (it == statetab.end() || it->second.empty()) {
            do {
                auto it2 = statetab.begin();
                std::advance(it2, std::rand() % statetab.size());
                it = it2;
            } while (it->second.empty());
            pref = it->first;
        }
        const auto& suffixes = it->second;
        int idx = std::rand() % static_cast<int>(suffixes.size());
        const std::string& next = suffixes[idx];
        output.push_back(next);
        pref.pop_front();
        pref.push_back(next);
    }
    return output;
}
