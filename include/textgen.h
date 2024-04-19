// Copyright 2024 alenkaLo
#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <deque>
#include <cstdlib>
#include <ctime>

typedef std::deque<std::string> prefix;
std::string generateText(int NPREF, int MAXGEN,
    prefix start, std::map<prefix,
    std::vector<std::string>> statetab);

std::string genWord(prefix* start, std::map<prefix,
    std::vector<std::string>> statetab, std::string* text);

std::map<prefix, std::vector<std::string>>
ReadFile(int NPREF, std::string path);
