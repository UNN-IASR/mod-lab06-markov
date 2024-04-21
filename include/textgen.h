//Copyright [year] <Copyright Owner>
#pragma once
#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <vector>

typedef std::deque<std::string> prefix;
class TextGen {
 public:
    std::map<prefix, std::vector<std::string> > statetab;
    prefix first;
    void StateTable(
        const std::map<prefix,
        std::vector<std::string>>&);
    TextGen();
    void makeTab(const std::string& text, int count);
    std::string generateText(int count, unsigned int time_count);
};
