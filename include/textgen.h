// Copyright 2022 UNN-IASR
#pragma once
#include <string>
#include <deque>
#include <vector>
#include <map>

class PROG {
 private:
    std::string data;
    std::vector<std::string> words;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    int NPREF;
    int MAXPROG;
 public:
    PROG(std::string arr, int val1, int val2);
    std::string getText();
    PROG(map<prefix, std::vector<std::string> > val,
    std::vector<std::string> words,
    int val1, int val2);
};
