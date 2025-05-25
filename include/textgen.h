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

typedef std::deque<std::string> prefix;  // prefix queue

class TextGenerator {
 public:
    TextGenerator(std::string FilePath, int prefixLen) {
        prefixLen_ = prefixLen;
        analyzeText(FilePath);
    }
    explicit TextGenerator(int prefixLen) { prefixLen_ = prefixLen; }

    std::string genText(int testLen);
    std::string genSuffix(const prefix& pref);

    void addTransition(
        const prefix& pref,
        const std::string& word);

    prefix getEnd() { return endPref_; }

 private:
    void analyzeText(const std::string& FilePath);

    int prefixLen_;
    prefix initPref_;
    prefix endPref_;
    std::map<prefix, std::vector<std::string> > statetab_;  // prefix-suffixes
};
#endif  // INCLUDE_TEXTGEN_H_
