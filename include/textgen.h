// Copyright 2022 UNN-IASR
#ifndef MOD_LAB06_MARKOV_INCLUDE_TEXTGEN_H_
#define MOD_LAB06_MARKOV_INCLUDE_TEXTGEN_H_
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
using namespace std;

class Generator {
 public:
    typedef deque<string> prefix;
    map<prefix, vector<string>> &getStateTable() { return statetab; }
    map<prefix, set<string>> &getPrefixSet() { return prefixSet; }
    string result;
    string getres() { return result; }
    int getNPref() const { return NPREF; }
    int getMaxGen() const { return MAXGEN; }
    explicit Generator() = default;
    explicit Generator(string testtext);
    void CreateText();
 private:
    map<prefix, vector<string>> statetab;
    map<prefix, set<string>> prefixSet;
    const int MAXGEN = 1000;
    const int NPREF = 2;
    void AnalisText();
};
#endif  // MOD_LAB06_MARKOV_INCLUDE_TEXTGEN_H_
