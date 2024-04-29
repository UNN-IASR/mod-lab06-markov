// Copyright 2024 Mikhas3009
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

namespace markov {
class MarkovChain {
 public:
    using Prefix = std::deque<std::string>;
    using Suffixes = std::vector<std::string>;
    std::map<Prefix, Suffixes> table;
    void train(const std::string& filename, int npref);
    std::string generate(int len, bool randfirst);

 private:
    std::mt19937 mt;
    void initializeRandomGenerator();
};
} //namespace markov
#endif  // INCLUDE_TEXTGEN_H_
