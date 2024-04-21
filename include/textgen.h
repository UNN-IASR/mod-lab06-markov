// Copyright 2024 Ignatyev Artyom

#pragma once

#include <stdlib.h>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

typedef std::deque<std::string> Prefix;

class Generator {
 private:
    std::map<Prefix, std::vector<std::string>> statetab;
 public:
    void createStatetab(std::istream &source, int prefixSize);
    std::string generateText(int length);
    std::map<Prefix, std::vector<std::string>> getStatetab();
    void setStatetab(std::map<Prefix, std::vector<std::string>> _chain);
};
