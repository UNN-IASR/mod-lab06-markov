// Copyright 2024 RuzKate

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <map>
#include <string>
#include <deque>
#include <vector>

typedef std::deque<std::string> Prefix;

class MarkovGenerator {
 private:
     Prefix startWord;
     std::map<Prefix, std::vector<std::string> > statetab;
 public:
     void CreateTable(std::string text, int count);
     std::string Generate(int textSize, unsigned int time_generate);
     std::map<Prefix, std::vector<std::string>> getTab();
     void trainFromStateTable(
         const std::map<Prefix,
         std::vector<std::string>>&);
};

#endif  // INCLUDE_TEXTGEN_H_
