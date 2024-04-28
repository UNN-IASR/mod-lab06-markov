// Copyright 2022 GHA Test Team

#pragma once
#include <stdlib.h>
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <random>
#include <fstream>

typedef std::deque<std::string> prefix;
typedef std::vector<std::string> suffixes;

class Markov {
 public:
    std::string GenerateText(std::string text, int sizePref, int maxLen);
    std::map<prefix, suffixes> GenerateStatetab(
        int sizePref, std::string text);
    std::string GetSuffix(suffixes suffixes);
    std::vector<std::string> Split(std::string text);
};

std::string ReadFile(std::string path);
