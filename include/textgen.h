// Copyright 2022 UNN-IASR
#pragma once
#include<stdlib.h>
#include<string>
#include<map>
#include<deque>
#include<vector>
class MarkovChain{
 public:
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    void Tab(std::vector<std::string> words, int NREF);
    std::string CreateText(int MAXGEN, unsigned int seed);
    prefix fpref;
};
