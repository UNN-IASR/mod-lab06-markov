//Copyright 2024 UNN-IASR
#pragma once
#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <vector>

typedef std::deque<std::string> prefix;
class TextGen {
 public:
    std::map<prefix, std::vector<std::string> > tab_state;
    prefix first;
    void StateTable(
        const std::map<prefix,
        std::vector<std::string>>&);
    TextGen();
    void create_tab(const std::string& text, int count);
    std::string generate(int count, unsigned int time_count);
};
