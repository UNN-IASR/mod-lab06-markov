// Copyright 2022 UNN-IASR
#pragma once
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class text_generator {
 public:
    explicit text_generator(std::size_t prefix_size) :
    prefix_size(prefix_size), data_base_power(0) {}
    void power_up(const std::string& file_path);
    void power_up(const std::vector<std::string>& words);
    std::string generate_text(std::size_t text_size, std::size_t words_in_line);
    void print_data_base();
    std::map<std::deque<std::string>,
    std::map<std::string, std::size_t>> get_base();
 private:
    std::map<std::deque<std::string>,
    std::map<std::string, std::size_t>> data_base;
    std::size_t data_base_power;
    std::size_t prefix_size;
};
