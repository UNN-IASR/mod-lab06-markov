// Copyright 2021 GHA Test Team
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <string>
#include <vector>

using Prefix = std::deque<std::string>;

using StateTable = std::map<Prefix, std::vector<std::string>>;

class TextGenerator {
 private:
  StateTable table;
  Prefix currentPrefix;
  int prefixLength;
  std::vector<Prefix> allPrefixes;

 public:
  explicit TextGenerator(int length = 2);
  void learnFromText(const std::string &filename);
  void generateText(int wordCount, const std::string &outputFile);
  std::vector<Prefix> GetAllPrefixes() { return allPrefixes; }
  StateTable GetTable() { return table; }
};

#endif // INCLUDE_TEXTGEN_H_
