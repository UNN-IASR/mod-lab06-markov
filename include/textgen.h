// Copyright 2022 UNN-IASR
#pragma once

#include <deque>
#include <map>
#include <string>
#include <vector>

class Markov {
 private:
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> statelab;
    int NPREF = 2;
    int MAXGEN = 1000;

 public:
    Markov(std::vector<std::string> allwords, int prfx_count, int gen_count);
    Markov(std::map<prefix, std::vector<std::string>> Gen, int gen_count);
    std::string TextGen();
};

