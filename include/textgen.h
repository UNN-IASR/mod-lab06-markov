  // Copyright 2022 Irina
#pragma once
#include <string>
#include <deque>
#include <vector>
#include <map>

class genText {
 public:
    std::string data;
    std::string getText();

    std::vector<std::string> words;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;  // prefix-suffix
    int NPREF;  // kol-vo slov s prefixe
    int MAXGEN;  // max kol-vo texta
    genText(std::string filename, int i1, int i2);
};
