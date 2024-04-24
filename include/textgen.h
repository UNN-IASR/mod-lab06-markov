// Copyright 2024 Yuriy Nazarov
#pragma once
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <queue>

typedef std::deque<std::string> Prefix;

class TextGen {
 public:
    TextGen();
    ~TextGen();
    void TextProcessing(const std::string&, int prefixLength);
    std::string GenerateText(int maxSize);
    std::map<Prefix, std::vector<std::string>> statetab;
 private:
    std::vector<std::string> splitText(const std::string&);
    Prefix startPrefix;
};
