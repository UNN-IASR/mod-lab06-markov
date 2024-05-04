// Copyright 2024 Matvey Bobrov
#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <string>

typedef std::deque<std::string> prefix;
typedef std::vector<std::string> suffix;

class Generator {
 public:
    std::string GenerateText(std::string text, int npref, int maxgen);
    std::map<prefix, suffix> GenerateTable(int npref, std::string text);
};

std::vector<std::string> Split(std::string text, std::string separator);
std::string ReadFile(std::string path);
