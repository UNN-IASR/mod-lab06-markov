// Copyright 2022 UNN-IASR
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>
#include "textgen.h"


TextGenerator::TextGenerator() {
    set_seed(std::time(nullptr));
}

void TextGenerator::set_seed(unsigned int seed) {
    gen.seed(seed);
}

std::string TextGenerator::clean_word(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (!std::ispunct(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

std::vector<std::string> TextGenerator::read_words_from_file(
    const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        std::string cleaned = clean_word(word);
        if (!cleaned.empty()) {
            words.push_back(cleaned);
        }
    }

    if (words.empty()) {
        std::cerr << "Warning: No words found in input file" << std::endl;
    }

    return words;
}

void TextGenerator::build_state_table(const std::string& filename) {
    auto words = read_words_from_file(filename);

    if (words.size() < NPREF) {
        std::cerr << "Warning: Input text is shorter than prefix length"
        << std::endl;
        return;
    }

    prefix pref;
    for (size_t i = 0; i < words.size() - NPREF + 1; ++i) {
        pref.clear();
        for (size_t j = 0; j < NPREF; ++j) {
            pref.push_back(words[i + j]);
        }
        if (i + NPREF < words.size()) {
            state_table[pref].push_back(words[i + NPREF]);
        }
    }
}

void TextGenerator::generate_text(const std::string& output_filename) {
    if (state_table.empty()) {
        std::cerr << "Error: State table is empty - nothing to generate"
        << std::endl;
        return;
    }

    std::ofstream out_file(output_filename);
    if (!out_file.is_open()) {
        std::cerr << "Error: Cannot open output file "
        << output_filename << std::endl;
        return;
    }

    current_prefix = GetRandomPrefix();
    int word_count = 0;

    while (word_count < MAXGEN) {
        out_file << current_prefix.back() << " ";
        word_count++;

        if (word_count % 10 == 0) {
            out_file << "\n";
        }

        auto suffixes = state_table.find(current_prefix);
        if (suffixes != state_table.end() && !suffixes->second.empty()) {
            std::uniform_int_distribution<> dist(0, suffixes->second.size() - 1);
            std::string next_word = suffixes->second[dist(gen)];
            current_prefix.pop_front();
            current_prefix.push_back(next_word);

        } else {
            current_prefix = GetRandomPrefix();
        }
    }

    out_file.close();
}

prefix TextGenerator::GetRandomPrefix() {
    if (state_table.empty()) {
        return {};
    }

    std::uniform_int_distribution<size_t> dist(0, state_table.size() - 1);
    auto it = state_table.begin();
    std::advance(it, dist(gen));
    return it->first;
}
