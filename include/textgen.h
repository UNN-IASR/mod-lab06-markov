// Copyright 2025 <A-Sabu>

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <ctime>

class Markov {
 public:
  Markov(int npref, int maxgen);
  Markov();
  void learnFromFile(const std::string& inputFileName);
  void learnFromString(const std::string& inputString);
  void generateText();
  void recordGeneratedTextToFile(const std::string& outputFileName);
  std::map<std::deque<std::string>, std::vector<std::string>>& getStateTable();
  std::string& getGeneratedText();

 private:
  typedef std::deque<std::string> Prefix;
  int NPREF;
  int MAXGEN;
  std::map<Prefix, std::vector<std::string>> statetab;
  std::string generatedText = "";
};
