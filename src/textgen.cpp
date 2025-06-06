// Copyright 2025 cherniuta
#include "../include/textgen.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <string>

TextGen::TextGen(int prefix_size) : prefix_size(prefix_size) {
    std::random_device rd;
    rng.seed(rd());
}

void TextGen::train(const std::string& filename) {
    std::ifstream file(filename);
    std::string word;
    std::deque<std::string> current_prefix;

    while (file >> word) {
        if (current_prefix.size() == prefix_size) {
            add(current_prefix, word);
            current_prefix.pop_front();
        }
        current_prefix.push_back(word);
    }
}

void TextGen::add(
    const std::deque<std::string>& prefix, const std::string& suffix
) {
    statetab[prefix].push_back(suffix);
}

std::string TextGen::get_random_suffix(const std::deque<std::string>& prefix) {
    const auto& suffixes = statetab[prefix];
    if (suffixes.empty()) return "";

    std::uniform_int_distribution<size_t> dist(0, suffixes.size() - 1);
    return suffixes[dist(rng)];
}

std::string TextGen::generate(int max_words) {
    if (statetab.empty()) return "";

    std::string result;
    std::deque<std::string> current_prefix;

    auto it = statetab.begin();
    current_prefix = it->first;

    for (const auto& word : current_prefix) {
        result += word + " ";
    }

    for (int i = current_prefix.size(); i < max_words; ++i) {
        std::string suffix = get_random_suffix(current_prefix);
        if (suffix.empty()) break;

        result += suffix + " ";
        current_prefix.pop_front();
        current_prefix.push_back(suffix);
    }

    return result;
}
