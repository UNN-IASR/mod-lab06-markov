// Copyright 2025 9hkge
#pragma once

#include <string>
#include <map>
#include <deque>
#include <vector>
#include <istream> 

typedef std::deque<std::string> prefix;

class TextGenerator {
 public:
  TextGenerator(int prefix_size, unsigned int random_seed);

  void create_suffix_map(std::istream &input);
  void create_suffix_map(std::map<prefix, std::vector<std::string>> map);
  std::map<prefix, std::vector<std::string>> get_suffix_map();
  std::string generate(int text_length);

 private:
  std::map<prefix, std::vector<std::string>> statetab;
  int prefix_size;
  unsigned int random_seed;
};
