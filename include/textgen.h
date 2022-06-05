// Copyright 2022 UNN
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#define rand_r rand

class Generator { 
 private:
    const int NPREF = 2;
    const int MAXGEN = 1000;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    std::vector<std::string> text;
 public:
    explicit Generator(std::string path);
    std::string newText();
    std::string Suffix(std::deque<std::string> prefdeq);
};
