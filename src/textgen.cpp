// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iterator>

void build_prefix_map(std::istream& in,
                      statetab_t& statetab, int npref) {
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
    const statetab_t& statetab, int npref, int maxgen) {
    std::vector<std::string> output;
    if (statetab.empty() || maxgen <= 0) return output;

    auto it_start = statetab.begin();
    std::advance(it_start, static_cast<int>(std::rand() % statetab.size()));
    std::deque<std::string> pref = it_start->first;

    std::copy(pref.begin(), pref.end(), std::back_inserter(output));

    while (static_cast<int>(output.size()) < maxgen) {
        auto it = statetab.find(pref);
        if (it == statetab.end() || it->second.empty()) {
            auto it2 = statetab.begin();
            std::advance(it2, static_cast<int>(std::rand() % statetab.size()));
            pref = it2->first;
            continue;
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
