// Copyright 2024 Maz

#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <fstream>
#include <random>
#include <ctime>
#include <iterator>
#include <sstream>

using u32    = uint_least32_t;
using engine = std::mt19937;
typedef std::deque<std::string> prefix;

std::vector<std::string> chstr_to_vecstr(const char* chtext);

void finput(std::deque<std::string>* arr);
void foutput(std::deque<std::string> arr);

void generate(std::map<prefix, std::vector<std::string> > state_tab);

std::map<prefix, std::vector<std::string> > make_statetab();
