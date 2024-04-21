// Copyright Mimi
#pragma once
#include<vector>
#include<locale>
#include<string>
#include<fstream>
#include<map>
#include<deque>
#include <iostream>
class Markov{
 public:
    unsigned int eeq = 50;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    prefix firstPref;
    prefix bufPref;
    void CreateStatetab(std::vector<std::string> words, int NREF);
    void OperationStatetab(std::string str);
    std::string CreateText(int MAXGEN);
};
