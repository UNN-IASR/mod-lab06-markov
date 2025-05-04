// Copyright 2024 Your Name
#include "textgen.h"
#include <fstream>
#include <random>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace {
const size_t kMaxGen = 1000;
const size_t kLineWrap = 20;
}  // namespace

TextGenerator::TextGenerator(const std::string& file_path, size_t prefix_length)
    : prefix_length_(prefix_length) {
    if (prefix_length_ == 0) {
        throw std::invalid_argument("Prefix length must be greater than 0");
    }
    AnalyzeText(file_path);
}

TextGenerator::TextGenerator(size_t prefix_length)
    : prefix_length_(prefix_length) {
    if (prefix_length_ == 0) {
        throw std::invalid_argument("Prefix length must be greater than 0");
    }
}

void TextGenerator::AnalyzeText(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    Prefix current_prefix;
    for (size_t i = 0; i < prefix_length_ && file; ++i) {
        std::string word;
        if (file >> word) {
            current_prefix.push_back(word);
        }
    }

    initial_prefix_ = current_prefix;
    
    std::string word;
    while (file >> word) {
        state_table_[current_prefix].push_back(word);
        current_prefix.pop_front();
        current_prefix.push_back(word);
    }
    
    end_prefix_ = current_prefix;
}

std::string TextGenerator::GenerateText(size_t text_length) const {
    if (initial_prefix_.empty()) {
        return "";
    }

    std::ostringstream text_stream;
    Prefix current_prefix = initial_prefix_;
    
    // Add initial prefix to the text
    for (const auto& word : current_prefix) {
        text_stream << word << " ";
    }

    // Generate the rest of the text
    for (size_t i = 0; i < text_length - prefix_length_; ++i) {
        if (current_prefix == end_prefix_) break;
        
        const std::string next_word = GenerateSuffix(current_prefix);
        text_stream << next_word << " ";
        
        if (i % kLineWrap == 0) {
            text_stream << "\n";
        }
        
        current_prefix.pop_front();
        current_prefix.push_back(next_word);
    }
    
    return text_stream.str();
}

std::string TextGenerator::GenerateSuffix(const Prefix& pref) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    const auto& suffixes = state_table_.at(pref);
    std::uniform_int_distribution<size_t> dist(0, suffixes.size() - 1);
    
    return suffixes[dist(gen)];
}

void TextGenerator::AddTransition(const Prefix& pref, const std::string& word) {
    if (initial_prefix_.empty()) {
        initial_prefix_ = pref;
    }
    state_table_[pref].push_back(word);
    end_prefix_ = {pref.back(), word};
}