//Copyright 2024 <levkovich-polina>
#pragma once
#include <stdexcept>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

class text {
 public:
  std::map<std::string, std::vector<std::string>> read(
      std::string filename,
      const std::map<std::string, std::vector<std::string>>& markovChain,
      int prefixLength);
  void generate(
      const std::map<std::string, std::vector<std::string>> markovChain,
      int prefixLength, int textLength);
  std::vector<std::string> prefix;
  std::string stop;
  std::string generateText;
};
