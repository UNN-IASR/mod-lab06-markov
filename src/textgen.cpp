// Copyright 2024 katione
#include <fstream>
#include <sstream>
#include <random>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>
#include "textgen.h"



void Text_Gen::text_file(int NPREF, const std::string& filestring) {
    std::string word;
    std::istringstream input_text(filestring);
    while (input_text >> word) {
        if (p_prefix.size() < NPREF) {
            p_prefix.push_back(word);
            p_refix = p_prefix;
        } else {
            statetab[p_prefix].push_back(word);
            p_prefix.pop_front();
            p_prefix.push_back(word);
        }
    }
}

std::string Text_Gen::text_generation(int MAXGEN_lenght , int ti_me) {
    srand((unsigned int)time(NULL));
    prefix pp_prefix = p_refix;
    std::string result = " ";
    int random;
    unsigned int random_time = time(NULL);
    for (auto i = pp_prefix.begin(); i != pp_prefix.end(); i++) {
        result += *i + " ";
    }

    for (int i = pp_prefix.size(); i < MAXGEN_lenght; i++) {
        if (statetab[pp_prefix].empty()) {
            break;
        }
        random = rand_r(&random_time) % statetab[pp_prefix].size();
        std::string suff = statetab[pp_prefix][random];
        result += suff + " ";
        pp_prefix.pop_front();
        pp_prefix.push_back(suff);
    }
    return result;
}
