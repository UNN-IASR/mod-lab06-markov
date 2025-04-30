// Copyright 2021 GHA Test Team
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

typedef std::deque<std::string> Prefix;

class TextGeneratorMarkov {
 public:
  explicit TextGeneratorMarkov(int prefixSize = 2, int maxWords = 1000);
  void loadText(const std::string &filename);
  void generateText(const std::string &outputFile);
  const std::map<Prefix, std::vector<std::string>> &getStateTable() const {
    return statetab;
  }
  std::string getRandomSuffixForTest(const Prefix &prefix) {
    return getRandomSuffix(prefix);
  }

 private:
  std::map<Prefix, std::vector<std::string>> statetab;
  int NPREF;
  int MAXGEN;
  std::mt19937 gen;

  void createStateTable(std::istream &input);
  void addSuffix(const Prefix &prefix, const std::string &suffix);
  std::string getRandomSuffix(const Prefix &prefix);
};

#endif // INCLUDE_TEXTGEN_H_
