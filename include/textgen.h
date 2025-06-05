// Copyright 2025 9hkge

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#endif  // INCLUDE_TEXTGEN_H_

#include <map>
#include <deque>
#include <string>
#include <vector>
#include <istream>
#include <ctime>

typedef std::deque<std::string> prefix;

class TextGenerator {
    public: 
        TextGenerator(int prefix_size = 2,
        unsigned int random_seed = time(NULL));
        void create_suffix_map(std::istream &input);
        void create_suffix_map(std::map<prefix, std::vector<std::string>> map);
        std::map<prefix, std::vector<std::string>> get_suffix_map();
        std::string generate(int text_length);
    private: 
        int prefix_size;
        unsigned int random_seed;
        std::map<prefix, std::vector<std::string>> statetab;
};