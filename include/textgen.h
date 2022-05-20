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
    std::string pair[2];
    std::string my_file;
    std::string words;
    typedef std::deque<std::string> prefix;
    prefix prefixes;
    std::vector<std::string> vector_words;
    std::vector<std::vector<std::string> > suffix;
    std::map<prefix, std::vector<std::string> > statetab;
    explicit TextGenerator(std::string file);
    void generate(int size);
    void read();
    void get_words();
    std::string get_list(std::string str);
    void make_dictionary();
    void get_connected();
    std::string calculate(int size);
    void write(std::string str);
};
