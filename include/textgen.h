// Copyright 2025 cherniuta
#pragma once

#include <deque>
#include <map>
#include <vector>
#include <string>
#include <random>

class TextGen {
 public:
    explicit TextGen(int prefix_size = 2);
    void train(const std::string& filename);
    std::string generate(int max_words);
    void add(const std::deque<std::string>& prefix, const std::string& suffix);
    std::string get_random_suffix(const std::deque<std::string>& prefix);

 private:
    std::deque<std::string> prefix;
    std::map<std::deque<std::string>, std::vector<std::string>> statetab;
    std::mt19937 rng;
    int prefix_size;
};
