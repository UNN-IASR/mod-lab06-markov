// Copyright 2024 Nekkozzz

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
#include <map>
#include <random>
#include <ctime>

using prefix = std::deque<std::string>;

class generator {
 private:
    std::map<prefix, std::vector<std::string> > map;
 public:
    void train(std::istream &source, int prefix_size);
    std::string generate_text(int length, unsigned int seed = time(NULL));
    void set_map(std::map<prefix, std::vector<std::string> > _map);
    std::map<prefix, std::vector<std::string> > get_map();
};

#endif  // INCLUDE_TEXTGEN_H_
