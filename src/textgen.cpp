// Copyright 2022 UNN-IASR
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>
#include <utility>
#include <map>
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
    return words;
}

void TextGenerator::build_state_table(const std::string& filename,
    int len_pref = NPREF) {
    auto words = read_words_from_file(filename);

    if (words.size() < len_pref) {
        throw std::runtime_error(
            "Warning: Input text is shorter than prefix length");
    }

    init_pref.clear();
    for (size_t i = 0; i < len_pref; ++i) {
        init_pref.push_back(words[i]);
    }

    prefix pref = init_pref;
    for (size_t i = len_pref; i < words.size(); ++i) {
        state_table[pref].push_back(words[i]);
        pref.pop_front();
        pref.push_back(words[i]);
    }

    end_pref.clear();
    for (size_t i = words.size() - len_pref; i < words.size(); ++i) {
        end_pref.push_back(words[i]);
    }
}

void TextGenerator::generate_text(const std::string& output_filename,
    int max_word) {
    if (state_table.empty()) {
        throw std::runtime_error("State table is empty - nothing to generate");
    }
    std::ofstream out_file(output_filename);
    if (!out_file.is_open()) {
        throw std::runtime_error("Cannot open output file: " + output_filename);
    }
    current_prefix = init_pref;
    int word_count = 0;
    for (const auto& word : current_prefix) {
        out_file << word << " ";
        word_count++;
    }

    while (word_count < max_word && current_prefix != end_pref) {
        auto suffixes = state_table.find(current_prefix);
        if (suffixes != state_table.end() && !suffixes->second.empty()) {
            std::string next_word = random_suff(current_prefix);
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

std::string TextGenerator::random_suff(prefix pref) {
    auto suffixes = state_table.find(pref);
    if (suffixes == state_table.end() || suffixes->second.empty()) {
        throw std::runtime_error("No suffixes found for the given prefix");
    }
    std::uniform_int_distribution<> dist(0, suffixes->second.size() - 1);
    return suffixes->second[dist(gen)];
}

void TextGenerator::add_pref(prefix pref, std::string word) {
    if (init_pref.size() == 0) init_pref = pref;
    state_table[pref].push_back(word);
    end_pref = {pref[pref.size() - 1], word};
}

std::map<prefix, std::vector<std::string>> TextGenerator::get_table() {
    return state_table;
}

prefix TextGenerator::get_init_pref() {
    return init_pref;
}

prefix TextGenerator::get_end_pref() {
    return end_pref;
}

void TextGenerator::add_end_pref(prefix end_preff) {
    end_pref = end_preff;
}

