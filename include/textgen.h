// Copyright 2024 Korshunov Yuriy

#pragma once

#include <stdlib.h>
#include<string>
#include<deque>
#include<map>
#include<vector>
#include <fstream>
#include <sstream>
#include<iostream>

typedef std::deque<std::string> Prefix;

class Generator {
 private:
    std::map<Prefix, std::vector<std::string>> chain;
 public:
    void Train(const std::string& text, int prefixSize);
    std::string Generate(int length, unsigned int seed = time(NULL));
    std::map<Prefix, std::vector<std::string>> getChain();
    void setChain(std::map<Prefix, std::vector<std::string>> _chain);
};
