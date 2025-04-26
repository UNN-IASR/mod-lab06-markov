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
    for (unsigned char c : word) {
        if (!std::ispunct(c)) {
            result += std::tolower(c);
        }
    }
    return result;
}

std::vector<std::string> TextGenerator::read_words_from_file(
    const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Can't open: " + filename);
    }

    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        std::string cleaned = clean_word(word);
        if (!cleaned.empty()) {
            words.push_back(std::move(cleaned));
        }
    }

    if (words.empty()) {
        std::cerr << "Warning: Empty file: " << filename << "\n";
    }

    return words;
}

void TextGenerator::build_state_table(const std::string& filename) {
    auto words = read_words_from_file(filename);

    if (words.size() < NPREF) {
        std::cerr << "Warning: Input text is shorter than prefix length" << std::endl;
        return;
    }

    init_pref.clear();
    for (size_t i = 0; i < NPREF; ++i) {
        init_pref.push_back(words[i]);
    }

    prefix pref = init_pref;
    for (size_t i = NPREF; i < words.size(); ++i) {
        state_table[pref].push_back(words[i]);
        pref.pop_front();
        pref.push_back(words[i]);
    }

    end_pref.clear();
    for (size_t i = words.size() - NPREF; i < words.size(); ++i) {
        end_pref.push_back(words[i]);
    }
}

void TextGenerator::generate_text(const std::string& output_filename) {
    if (state_table.empty()) {
        std::cerr << "Error: State table is empty - nothing to generate" << std::endl;
        return;
    }
    std::ofstream out_file(output_filename);
    if (!out_file.is_open()) {
        std::cerr << "Error: Cannot open output file " << output_filename << std::endl;
        return;
    }
    current_prefix = init_pref;
    int word_count = 0;
    for (const auto& word : current_prefix) {
        out_file << word << " ";
        word_count++;
    }

    while (word_count < MAXGEN && current_prefix != end_pref) {
        auto suffixes = state_table.find(current_prefix);
        if (suffixes != state_table.end() && !suffixes->second.empty()) {
            std::uniform_int_distribution<> dist(0, suffixes->second.size() - 1);
            std::string next_word = suffixes->second[dist(gen)];
            out_file << next_word << " ";
            word_count++;

            if (word_count % 15 == 0) {
                out_file << "\n";
            }

            current_prefix.pop_front();
            current_prefix.push_back(next_word);
        } else {
            break;
        }
    }
    out_file.close();
}
