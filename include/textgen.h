// Copyright 2024 Shelnov Yuriy
#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#define rand_r rand

const int INITIAL_PREFIX_SIZE = 2;
const int GENERATION_LIMIT = 1000;

class TextGenerator {
 private:
    int currentPrefixLength;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > stateTable;
    std::vector<std::string> wordPool;
 public:
    TextGenerator(std::string InputFile, int preflen);
    std::string getText(int wordPoolamount);
    int getCurrentPrefixLength();
    std::string getSuffix(std::deque<std::string> prefdeq);
    void WriteOnFileGenerateText(int wordPoolamount);
};
