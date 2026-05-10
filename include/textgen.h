#pragma once
#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <random>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string> > statetab;

void build_table(std::ifstream& input, statetab& table, int npref);
void generate_text(statetab& table, int npref, int maxgen);

#endif
