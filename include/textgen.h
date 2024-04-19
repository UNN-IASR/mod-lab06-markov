// Copyright 2024 mpv-enjoyer
#pragma once
#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <vector>

class TextGen {
 public:
    typedef std::deque<std::string> prefix;
 private:
    std::map<prefix, std::vector<std::string>> statetab;
    prefix first_prefix;
    int prefix_size;
 public:
    TextGen(std::istream &input, int prefix_number);
    explicit TextGen(std::map<prefix, std::vector<std::string>> s);
    std::string CreateText(int length);
    std::string CreateText(int length, int seed);
    const std::map<prefix, std::vector<std::string>>& states();
};
