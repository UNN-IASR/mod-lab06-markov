#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>

typedef std::deque<std::string> prefix;

class TextGen {
public:
    static const int NPREF = 2;

    std::map<prefix, std::vector<std::string>> statetab;

    void clear();

    void readText(std::istream& in);

    std::string generate(int nwords);

    size_t getTableSize() const { return statetab.size(); }
};
