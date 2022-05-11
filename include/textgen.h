// Copyright 2022 UNN-IASR
#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#define rand_r rand

const int NPREF = 2;
const int MAXGEN = 1000;

class MarkovGenerator {
 private:
    int prefixSize;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    std::vector<std::string> words;
 public:
    MarkovGenerator(std::string path, int preflen);
    std::string getText(int wordsamount);
    int getPrefixSize();
    std::string getSuffix(std::deque<std::string> prefdeq);
};
