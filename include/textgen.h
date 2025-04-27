// Copyright 1901 Romanchik333
#pragma once

#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using prefix = std::deque<std::string>;

class TextGenerator {
 public:
    explicit TextGenerator(size_t pref_len = 2);

    explicit TextGenerator(std::ifstream& input_file, size_t pref_len = 2);

    std::string Generate(size_t size, unsigned int seed);

    static std::string ReadAllFromFile(std::ifstream& input);

    void PrintTable(std::ostream& out);

    std::map<prefix, std::vector<std::string>>& statetab();

 private:
    const size_t NPREF;
    const size_t MAXGEN = 1000;
    std::map<prefix, std::vector<std::string>> statetab_;

    prefix GetRandomPrefix_(unsigned int seed);

    static std::string PrepareText_(const std::string& text);
};
