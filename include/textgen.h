// Copyright 2022 UNN-IASR
#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <cctype>

typedef std::deque<std::string> prefix;

class TextGenerator {
  private:
    std::map<prefix, std::vector<std::string>> state_table;
    prefix current_prefix;
    std::mt19937 gen;

    static constexpr int NPREF = 2;       
    static constexpr int MAXGEN = 1000;   

    std::string clean_word(const std::string& word);
    std::vector<std::string> read_words_from_file(const std::string& filename);
    prefix GetRandomPrefix();


  public:
    TextGenerator();
    void set_seed(unsigned int seed);
    void build_state_table(const std::string& filename);  
    void generate_text(const std::string& output_filename);               
};

#endif // TEXTGEN_H