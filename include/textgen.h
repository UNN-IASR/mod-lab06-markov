// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>


class Generator {
 public:
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> &getStateTable() {
     return statetab;
    }
    std::map<prefix, std::set<std::string>> &getPrefixSet() {
     return prefixSet;
    }
    std::string result;
    int fl = 0;
    std::deque<std::string> first;
    std::string getres() { return result; }
    int getNPref() const { return NPREF; }
    int getMaxGen() const { return MAXGEN; }
    explicit Generator() = default;
    explicit Generator(std::string testtext);
    void CreateText();
 private:
    std::map<prefix, std::vector<std::string>> statetab;
    std::map<prefix, std::set<std::string>> prefixSet;
    const int MAXGEN = 1000;
    const int NPREF = 2;
    void AnalisText();
};
#endif  // INCLUDE_TEXTGEN_H_
