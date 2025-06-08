#include "textgen.h"
#include <sstream>
#include <cstdlib>
#include <iterator>

void build_prefix_map(std::istream& in, statetab_t& statetab, int npref) {
    std::deque<std::string> pref;
    std::string word;
    // Initialize prefix with first npref words
    for (int i = 0; i < npref; ++i) {
        if (!(in >> word)) return;
        pref.push_back(word);
    }
    // Read remaining words and build map
    while (in >> word) {
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }
}

std::vector<std::string> generate_text(const statetab_t& statetab, int npref, int maxgen) {
    std::vector<std::string> output;
    if (statetab.empty() || maxgen <= 0) return output;

    // Seed initial prefix randomly from available keys
    auto it_start = statetab.begin();
    std::advance(it_start, std::rand() % statetab.size());
    std::deque<std::string> pref = it_start->first;

    // Copy initial prefix words to output
    std::copy(pref.begin(), pref.end(), std::back_inserter(output));

    // Generate until reaching maxgen words
    while ((int)output.size() < maxgen) {
        auto it = statetab.find(pref);
        if (it == statetab.end() || it->second.empty()) {
            // Restart from a random prefix to continue
            auto it2 = statetab.begin();
            std::advance(it2, std::rand() % statetab.size());
            pref = it2->first;
            continue;
        }
        const auto& suffixes = it->second;
        int idx = std::rand() % suffixes.size();
        const std::string& next = suffixes[idx];
        output.push_back(next);
        pref.pop_front();
        pref.push_back(next);
    }
    return output;
}
