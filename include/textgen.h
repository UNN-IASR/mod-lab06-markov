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

using PrefixDeque = std::deque<std::string>;

class MarkovChain {
 public:
    MarkovChain(const std::string& inputFile, int prefixSize) : nPrefix(prefixSize) {
        buildStateTable(inputFile);
    }
    
    explicit MarkovChain(int prefixSize) : nPrefix(prefixSize) {}

    std::string generate(int outputSize);
    std::string getNextWord(const PrefixDeque& currentPrefix);
    void addWordTransition(const PrefixDeque& prefix, const std::string& nextWord);
    
    PrefixDeque getFinalPrefix() const { return lastPrefix; }

 private:
    int nPrefix;
    PrefixDeque firstPrefix;
    PrefixDeque lastPrefix;
    std::map<PrefixDeque, std::vector<std::string>> transitions;
    
    void buildStateTable(const std::string& inputFile);
};
#endif  // INCLUDE_TEXTGEN_H_