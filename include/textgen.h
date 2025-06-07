// Copyright 2025 AirFox

#pragma once

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const int prefixSize = 2;
const int maxGenWords = 1000;

using Prefix = std::deque<std::string>;
using Chain = std::map<Prefix, std::vector<std::string>>;

void build(std::ifstream& in, Chain& chain);
void generate(std::ofstream& out, Chain& chain);
