// Copyright 2022 UNN-IASR
#include "textgen.h"

#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

const int NPREF = 2;
const int MAXGEN = 1000;

TextGenerator::TextGenerator(const std::string& filepath, int prefix_length) {
  if (prefix_length <= 0) {
    throw std::invalid_argument("Prefix length must be positive");
  }
  prefix_len = prefix_length;
  analyzeText(filepath);
}

void TextGenerator::analyzeText(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file) {
    throw std::runtime_error("File not found: " + filepath);
  }

  prefix pref;
  std::string word;

  for (int i = 0; i < prefix_len; ++i) {
    if (!(file >> word)) {
      throw std::runtime_error("File too short for prefix length");
    }
    pref.push_back(word);
  }
  init_pref = pref;

  while (file >> word) {
    statetab[pref].push_back(word);
    pref.push_back(word);
    pref.pop_front();
  }

  if (statetab.empty()) {
    throw std::runtime_error("Not enough data for transitions");
  }
  end_pref = pref;
}

std::string TextGenerator::genText(int min_words, int max_words) {
  if (min_words > max_words) {
    throw std::invalid_argument("Invalid word count range");
  }
  if (statetab.empty()) return "";

  std::string result;
  prefix current = init_pref;
  int word_count = 0;

  for (const auto& word : current) {
    if (word_count >= max_words) break;
    result += word + " ";
    ++word_count;
  }

  while (word_count < max_words) {
    if (current == end_pref || !statetab.count(current)) {
      current = init_pref;
      continue;
    }

    std::string next_word = genSuffix(current);
    result += next_word + " ";
    ++word_count;

    if (word_count % 20 == 0) result += "\n";
    current.push_back(next_word);
    current.pop_front();
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

std::string TextGenerator::genSuffix(const prefix& pref) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> dist(0, statetab.at(pref).size() - 1);
  return statetab.at(pref)[dist(gen)];
}

void TextGenerator::addTransition(const prefix& pref, const std::string& word) {
  if (init_pref.empty()) {
    init_pref = pref;
  }
  statetab[pref].push_back(word);
  end_pref = prefix(pref.begin() + 1, pref.end());
  end_pref.push_back(word);
}
