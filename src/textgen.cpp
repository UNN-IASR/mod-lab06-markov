// Copyright 2022 UNN-IASR
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include "textgen.h"

TextGenerator::TextGenerator(int npref, int maxgen)
    : NPREF(npref), MAXGEN(maxgen) {
  gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void TextGenerator::build(std::istream& in) {
  std::string word;
  prefix current_prefix;

  for (int i = 0; i < NPREF && in >> word; ++i) {
    current_prefix.push_back(word);
  }

  first_prefix = current_prefix;

  while (in >> word) {
    if (current_prefix.size() == NPREF) {
      add_suffix(current_prefix, word);
      current_prefix.pop_front();
      current_prefix.push_back(word);
    }
  }
}

void TextGenerator::add_suffix(const prefix& p, const std::string& s) {
  state_tab[p].push_back(s);
}

std::string TextGenerator::get_random_suffix(
    const std::vector<std::string>& suffixes) {
  if (suffixes.empty()) {
    throw std::runtime_error("No suffixes available");
  }

  std::uniform_int_distribution<> dist(0, suffixes.size() - 1);
  return suffixes[dist(gen)];
}

void TextGenerator::generate(std::ostream& out) {
  if (state_tab.empty()) {
    throw std::runtime_error("No data to generate text");
  }

  prefix current_prefix = first_prefix;
  if (current_prefix.size() < NPREF) {
    throw std::runtime_error("Not enough words in the first prefix");
  }

  int words_generated = 0;
  for (const auto& word : current_prefix) {
    if (words_generated >= MAXGEN) break; // Проверяем лимит перед выводом
    out << word << " ";
    words_generated++;
  }

  while (words_generated < MAXGEN) {
    auto it = state_tab.find(current_prefix);
    if (it == state_tab.end() || it->second.empty()) {
      break;
    }

    std::string next_word = get_random_suffix(it->second);
    out << next_word << " ";
    current_prefix.pop_front();
    current_prefix.push_back(next_word);
    words_generated++;

    if (words_generated % 10 == 0 && words_generated < MAXGEN) {
      out << "\n";
    }
  }
}
