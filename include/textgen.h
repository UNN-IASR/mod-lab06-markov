// Copyright 2024 Goncharova Anna
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <vector>

class Generator {
 public:
    typedef std::deque<std::string> prefix;
    prefix _prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    void creating_statetab(const std::string& string, int size);
    std::string Text_generator(int maxgen, int time_generate);
    void trainFromStateTable(const std::map<prefix, std::vector<std::string>>&);
};
#endif //INCLUDE_TEXTGEN_H_
