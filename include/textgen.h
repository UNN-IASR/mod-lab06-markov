#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <random>

// Copyright 2024

class TextGen{
 private:
 public:
     explicit TextGen(std::string);
     std::map<std::string, std::vector<std::string>> states;
     std::string Generate(int n);
     std::vector<std::string>::iterator
     select_randomly(std::vector<std::string>::iterator start,
                     std::vector<std::string>::iterator end);
     std::vector<std::string>::iterator
     select_randomly(std::vector<std::string>::iterator start,
     std::vector<std::string>::iterator end, std::mt19937 g);
};

