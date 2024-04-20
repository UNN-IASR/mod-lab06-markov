// Copyright 2024 Galanin Andrey
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <vector>

typedef std::deque<std::string> prefix;  // очередь префиксов

class GenerationText {
 private:
    std::map<prefix, std::vector<std::string>> statetab; // префикс-суффиксы
    prefix fprefix;
 public:
    void Learn(const std::string& string, int prefix_number);
    std::string Create(int length, int seed);
    void set(std::map<prefix, std::vector<std::string>> string);
    std::map<prefix, std::vector<std::string>> get();
};

#endif  // INCLUDE_TEXTGEN_H_
