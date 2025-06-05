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
  if(text_length <= 0) {
      return "";
  }
  std::string result = "";

  auto statetab_copy = statetab;
  auto begin = statetab_copy.begin();

  auto prefix = begin->first;
  for(auto prefix_it = prefix.begin(); prefix_it != prefix.end(); prefix_it++) {
      result += *prefix_it + " ";
  }

  for(int i = prefix_size; i < text_length; i++) {
      if(statetab_copy[prefix].empty()) {
          break;
      }
      
      int random_suffix_index = rand() % statetab_copy[prefix].size();
      std::string word = statetab_copy[prefix][random_suffix_index];
      
      result += word + " ";
      
      statetab_copy[prefix].erase(statetab_copy[prefix].begin() + random_suffix_index);
      
      prefix.pop_front();
      prefix.push_back(word);
  }

  return result;
}
