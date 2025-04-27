// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

typedef std::deque<std::string> prefix;  // очередь префиксов

class TextGenerator {
 public:
  TextGenerator(std::string FilePath, int prefix_le) {
    prefix_len = prefix_le;
    analyzeText(FilePath);
  }
  explicit TextGenerator(int prefix_le) { prefix_len = prefix_le; }
  std::string genText(int text_len);
  std::string genSuffix(prefix pref);
  void addTransition(prefix pref, std::string word);
  prefix getEnd() { return end_pref; }

 private:
  int prefix_len;
  prefix init_pref;
  prefix end_pref;
  std::map<prefix, std::vector<std::string> > statetab;  // префикс-суффиксы
  void analyzeText(std::string FilePath);
};
#endif  // INCLUDE_TEXTGEN_H_
