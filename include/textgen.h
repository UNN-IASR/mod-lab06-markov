#pragma once
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <fstream>

const int prefixSize = 2;
const int maxGenWords = 1000; 

typedef std::deque<std::string> Prefix;
typedef std::map<Prefix, std::vector<std::string>> Chain;

void build(std::ifstream& in, Chain& chain);
void generate(std::ofstream& out, Chain& chain);
