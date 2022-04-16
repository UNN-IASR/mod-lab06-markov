// Copyright 2022 UNN-IASR
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <random>


const int NPREF = 2;
const int MAXGEN = 1000;

class TextGenerator {
 public:
    int result_len;
    int index;
    std::string pair[2];
    std::string my_file;
    std::string words;
    typedef std::deque<std::string> prefix;
    prefix prefixes;
    std::vector<std::string> slova;
    std::vector<std::vector<std::string> > suffix;
    std::map<prefix, std::vector<std::string> > statetab;
    explicit TextGenerator(std::string file);
    void generate(int size);
    void read_from_file();
    void get_words();
    void find_suffix();
    void write_to_file(std::string str);
    void get_connected();
    std::string get_result(int size);
    std::string get_list_of_strings(std::string str);
};
