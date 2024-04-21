//  Copyright 2024 Teodor
#ifndef SRC_TEXTGEN_H_
#define SRC_TEXTGEN_H_

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <random>

typedef std::deque<std::string> prefix;
typedef std::vector<std::string> postfix;
bool is_separator(char c);
std::vector<std::string> Split(std::string in_string);
std::vector<std::string> Split_file_lines(std::string name_of_file);
std::vector<std::string> Generating_text(std::string name_of_file,
                                        int NPREF, int MAXGEN);
prefix get_pref(std::vector<std::string> words, int NPREF);
void add_new_row(std::map<prefix, postfix> &statetab,
                prefix& pre,
                const std::vector<std::string>& words,
                int i);
bool add_new_string(std::map<prefix, postfix> &statetab,
prefix& pre, std::vector<std::string>& out_string);
std::map<prefix, postfix> create_statetab(const std::vector<std::string> &words,
                                            int NPREF);
std::vector<std::string> get_text(std::map<prefix, postfix> &statetab,
        const std::vector<std::string> &words, int NPREF, int MAXGEN);
#endif // SRC_TEXTGEN_H_
