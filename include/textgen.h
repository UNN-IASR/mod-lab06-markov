// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <string>
#include <vector>

typedef std::deque<std::string> prefix;

class TextGenerator {
 private:
  int prefix_len;
  prefix init_pref;
  prefix end_pref;
  std::map<prefix, std::vector<std::string>> statetab;

 public:
  TextGenerator(const std::string& filepath, int prefix_length);
  explicit TextGenerator(int prefix_length);
  std::string genText(int min_words = 1000, int max_words = 1500);
  std::string genSuffix(const prefix& pref);
  void addTransition(const prefix& pref, const std::string& word);
  prefix getEnd() const { return end_pref; }

 private:
  void analyzeText(const std::string& filepath);
};

#endif  // INCLUDE_TEXTGEN_H_
