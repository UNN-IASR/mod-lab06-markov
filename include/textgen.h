// Copyright 2024 Vladislav Labutin

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

class markov {
 public:
    typedef std::deque<std::string> prefix;
    typedef std::vector<std::string> suffixes;
    std::map<prefix, suffixes> table;
    void train(const std::string& filename, int npref);
    std::string generate(int len, bool randfirst);
};

#endif  // INCLUDE_TEXTGEN_H_
