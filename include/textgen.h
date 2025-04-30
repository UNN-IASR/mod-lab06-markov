// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include <deque>
//#include <random>

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;

class TextGeneratorClass {
 public:
  explicit TextGeneratorClass(std::string Filepath);
  std::string generateText();
  std::map < prefix, std::vector<std::string>> buildStateTab
  (std::vector<std::string> words);
  prefix GetStartPrefix();
  void SetStartPrefix(prefix newStartPrefix);
  std::map < prefix, std::vector<std::string>> GetStateTab();
  void SetStateTab(std::map < prefix, std::vector<std::string>> newStateTab);
  std::string chooseNextWord(prefix pref, std::mt19937 gen);
 private:
  std::vector<std::string> readWords(std::string Filepath);
  std::map < prefix, std::vector<std::string>> stateTab;
  prefix start_prefix;
  prefix end_prefix;
};

#endif  // INCLUDE_TEXTGEN_H_
