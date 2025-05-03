// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <vector>
#include <string>
#include <random> 

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

class MarkovTextGenerator {
 private:
       statetab table;
       prefix startPref;
       std::mt19937 rng;

 public:
       MarkovTextGenerator();

       std::string generateText();

       void createTable(const std::vector<std::string>& words);
};

#endif //INCLUDE_TEXTGEN_H_
