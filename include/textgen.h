// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

class TextGenerator {
 private:
  int prefLenght = 0;
  std::vector<std::string> readFile(const std::string& filename);

 public:
  statetab table;
  prefix firstPrefix;
  TextGenerator();
  void createTable(const std::string& filename, int prefLenght);
  void generateText(int maxCount, const std::string& filename);
};

#endif  // INCLUDE_TEXTGEN_H_
