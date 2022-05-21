// Copyright 2022 UNN-IASR
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <random>
class Gen {
 private:
    string data;
    vector<string> words;
    typedef deque<string> prefix;
    map<prefix, vector<string> > statetab;
    int NPREF, MAXGEN;
 public:
    Gen(string arr, int val1, int val2);
    string getText();
    Gen(map<prefix, vector<string> > val, vector<string> words, int, int);
};
