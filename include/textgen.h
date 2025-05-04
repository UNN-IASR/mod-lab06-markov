#pragma once
#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <vector>
#include <map>
#include <string>
#include <iostream>

class TextGenerator {
public:
    static const int NPREF = 2;
    static const int MAXGEN = 1000;

    void build(std::istream& in);
    void generate(int nwords, const std::string& outputFile = "gen.txt");
    
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> statetab;
    prefix initialPrefix;

    void add(prefix& p, const std::string& s);
};

#endif