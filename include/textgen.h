// Copyright 2024 Annenko Misha
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <random>
#include <cstdlib>

class textgen {
 public:
    // очередь префиксов
    typedef std::deque<std::string> prefix;
    // префикс-суффиксы
    std::map<prefix, std::vector<std::string> > statetab;

    void memorization(const std::string& input_text, int npref);
    std::string generate__text(int maxgen, int npref);
    std::string generate_text(int maxgen, int npref, int seed);

    void Manual_Table(
        const std::map<prefix,
    std::vector<std::string>>& state);
 private:
    prefix FirstPref;
    std::vector<std::string> Split(const std::string& str);
};
