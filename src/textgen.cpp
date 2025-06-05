// Copyright 2025 9hkge
#include "textgen.h"
#include <random>

TextGenerator::TextGenerator(int prefix_size, unsigned int random_seed) {
    this->random_seed = random_seed;
    this->prefix_size = prefix_size;
}

void TextGenerator::create_suffix_map(std::istream &input) {
  std::string word;
  prefix prefix;
  
  while(input >> word) {
      if(prefix.size() == prefix_size) {
          statetab[prefix].push_back(word);
          prefix.pop_front();
      }
      
      prefix.push_back(word);
  }
}

void TextGenerator::create_suffix_map(std::map<prefix, std::vector<std::string>> map) {
  statetab = map;
}

std::map<prefix, std::vector<std::string>> TextGenerator::get_suffix_map() {
  return statetab;
}

std::string TextGenerator::generate(int text_length) {
  if (text_length <= 0 || statetab.empty()) {
      return "";
  }

  std::string result = "";

  auto statetab_copy = statetab;
  auto begin = statetab_copy.begin();

  auto prefix = begin->first;
  for (const auto& w : prefix) {
      result += w + " ";
  }

  for (int i = prefix_size; i < text_length; ++i) {
      auto it = statetab_copy.find(prefix);
      if (it == statetab_copy.end() || it->second.empty())
          break;

      int index = rand() % it->second.size();
      std::string word = it->second[index];
      result += word + " ";

      it->second.erase(it->second.begin() + index);
      if (it->second.empty())
          statetab_copy.erase(prefix);

      prefix.pop_front();
      prefix.push_back(word);
  }

  return result;
}

