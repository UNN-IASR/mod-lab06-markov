#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Generator
{
public:
    typedef deque<string> prefix;
    map<prefix, vector<string>> &getStateTable() { return statetab; };
    map<prefix, set<string>> &getPrefixSet() { return prefixSet; };
    int getNPref() const { return NPREF; };
    int getMaxGen() const { return MAXGEN; };
    Generator() = default;
    Generator(string testtext);
    void CreateText();

private:
    map<prefix, vector<string>> statetab;
    map<prefix, set<string>> prefixSet;
    const int MAXGEN = 1000;
    const int NPREF = 2;
    void AnalisText();
};