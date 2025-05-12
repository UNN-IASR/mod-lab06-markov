// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <random>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>

typedef std::deque<std::string> prefix;

class TextGenerator {
 private:
    std::map<prefix, std::vector<std::string>> state_table;
    prefix current_prefix;
    std::mt19937 gen;
    prefix init_pref;
    prefix end_pref;

    std::string clean_word(const std::string& word);
    std::vector<std::string> read_words_from_file(const std::string& filename);
    void set_seed(unsigned int seed);

 public:
    static constexpr int NPREF = 2;
    static constexpr int MAXGEN = 1300;

    TextGenerator();
    void build_state_table(const std::string& filename, int len_pref);
    void generate_text(const std::string& output_filename, int max_word);
    std::string random_suff(prefix prefix);
    void add_pref(prefix pref, std::string word);
    std::map<prefix, std::vector<std::string>> get_table();
    prefix get_init_pref();
    prefix get_end_pref();
    void add_end_pref(prefix end_preff);
};
#endif // INCLUDE_TEXTGEN_H_
