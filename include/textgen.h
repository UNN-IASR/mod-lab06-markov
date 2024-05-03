// Copyright 2024 katione
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <string>
#include <iostream>
#include <deque>
#include <map>
#include <ctime>
#include <vector>
#pragma once

class Text_Gen {
 public:
    typedef std::deque<std::string> prefix;
    prefix p_refix;
    prefix p_prefix;
    std::map<prefix, std::vector<std::string>> statetab;
    void text_file(int NPREF, const std::string& file);
    std::string text_generation(int MAXGEN_lenght , int ti_me);
};

#endif  // INCLUDE_TEXTGEN_H_
