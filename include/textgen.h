#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>

class Generator {
    
private:
    const int NPREF = 2;
    const int MAXGEN = 1000;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > statetab;
    std::vector<std::string> text;
    
public:
    Generator(std::string path);
    std::string newText();
    std::string Suffix(std::deque<std::string> prefdeq);
};
