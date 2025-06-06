// Copyright 2025 9hkge

#include <cstdlib>  // for rand_r
#include <utility>
#include <string>
#include <map>
#include <vector>
#include <random>
#include <deque>  // prefix — скорее всего deque
#include "textgen.h"


TextGenerator::TextGenerator(int prefix_size, unsigned int random_seed) {
  this->random_seed = random_seed;
  this->prefix_size = prefix_size;
}

void TextGenerator::create_suffix_map(std::istream &input) {
  std::string word;
  prefix prefix;

  while (input >> word) {
    if (prefix.size() == prefix_size) {
      statetab[prefix].push_back(word);
      prefix.pop_front();
    }
    prefix.push_back(word);
  }
}

void TextGenerator::create_suffix_map(
    std::map<prefix, std::vector<std::string>> map) {
  statetab = std::move(map);
}

std::map<prefix, std::vector<std::string>> TextGenerator::get_suffix_map() {
  return statetab;
}

std::string TextGenerator::generate(int text_length) {
  if (text_length <= 0) {
      return "";
  }

  std::string result;
  auto statetab_copy = statetab;


  std::vector<prefix> keys;
  for (const auto& entry : statetab) {
      keys.push_back(entry.first);
  }

  std::mt19937 gen(random_seed);
  std::uniform_int_distribution<> dist(0, keys.size() - 1);

  prefix prefix = keys[dist(gen)];





  for (const auto& word : prefix) {
      result += word + " ";
  }


  for (int i = prefix_size; i < text_length; ++i) {
      auto& suffixes = statetab_copy[prefix];
      if (suffixes.empty()) {
          break;
      }

      std::uniform_int_distribution<> suffix_dist(
        0, static_cast<int>(suffixes.size()) - 1);
    
      int random_suffix_index = suffix_dist(gen);
      std::string word = suffixes[random_suffix_index];

      result += word + " ";

      suffixes.erase(suffixes.begin() + random_suffix_index);

      prefix.pop_front();
      prefix.push_back(word);
  }

  return result;
}
