// Copyright 2022 UNN-IASR
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>
#include "textgen.h"

void TextGenerator::__create_state_table__(
    const std::string& file_path, 
    size_t prefix_length
) {
    std::vector<std::string> words = __get_words_from_file__(file_path);

    prefix p;
    for (size_t j = 0; j < prefix_length; ++j) {
        p.push_back(words[j]);
    }
    _first_prefix = p;

    _table = __generate_state_table__(words, prefix_length);
}

std::vector<std::string> TextGenerator::__get_words_from_file__(
    const std::string& file_path
) {
    std::ifstream file(file_path);
    std::vector<std::string> words;

    if (!file.is_open()) {
        std::ostringstream oss;
        oss << "Failed to open file " << file_path;

        throw std::ifstream::failure(oss.str());
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();

    return words;
}

statetab TextGenerator::__generate_state_table__(
    const std::vector<std::string>& words, 
    size_t prefix_length
) {
    statetab table;

    for (size_t i = 0; i < words.size() - prefix_length; i++) {
        prefix p;
        for (size_t j = 0; j < prefix_length; ++j) {
            p.push_back(words[i + j]);
        }
        table[p].push_back(words[i + prefix_length]);
    }

    return table;
}

void TextGenerator::__generate_text_and_write_to_file__(
    size_t max_words, 
    const std::string& file_path
) {
    std::string generated_text = __generate_text__(max_words);

    __write_text_to_file__(file_path, generated_text);
}

std::string TextGenerator::__generate_text__(size_t max_words) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> distribution;

    prefix current_prefix = _first_prefix;

    std::string generated_text;

    for (const auto& word : current_prefix) {
        generated_text += word + " ";
    }

    size_t word_count = current_prefix.size();

    while (word_count < max_words) {
        auto it = _table.find(current_prefix);
        if (it == _table.end()) {
            break;
        }

        const auto& suffixes = it->second;

        std::string next_word = suffixes[distribution(gen) % suffixes.size()];

        generated_text += next_word + " ";
        word_count++;

        current_prefix.pop_front();
        current_prefix.push_back(next_word);
    }

    return generated_text;
}

void TextGenerator::__write_text_to_file__(
    const std::string& file_path, 
    const std::string& text
) {
    std::ofstream out(file_path);
    if (!out.is_open()) {
        throw std::ios_base::failure("Failed to open file for writing");
    }

    out << text;

    if (!out) {
        throw std::ios_base::failure("Error occurred while writing to file");
    }

    out.close();
}

const statetab& TextGenerator::__get_state_table__() {
    return _table;
}
