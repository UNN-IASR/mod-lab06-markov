// Copyright 2024 Vyacheslav Bolshakov
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <random>
#include <climits>

typedef std::deque<std::string> prefix;

class MGenerator {
 public:
    std::map<prefix, std::vector<std::string>> statetab;
    std::vector<prefix> prefixes;
    void read_file(const char* filename, int n);
    void read_text(std::string text, int n);
    std::string generate_text(int nwords);
};

#endif  // INCLUDE_TEXTGEN_H_
