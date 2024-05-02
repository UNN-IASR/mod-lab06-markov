// Copyright 2024 Kokorin Alexandr

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#pragma once
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <string>

class textgen {
 public:
    typedef std::deque<std::string> Prefix;
    Prefix prefix;
    std::map<Prefix, std::vector<std::string> > stateTable;

 public:
    textgen(const std::string& text, int prefixLength);
    explicit textgen(const std::map<Prefix,
        std::vector<std::string>>& stateTable);
    std::string generate(int maxgen);
};
#endif  // INCLUDE_TEXTGEN_H_
