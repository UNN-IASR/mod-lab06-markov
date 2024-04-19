// Copyright 2024 mpv-enjoyer
#include <fstream>
#include <random>
#include <functional>
#include "textgen.h"

typedef std::uniform_int_distribution<std::mt19937::result_type> std_distr;

TextGen::TextGen(std::istream& input, int prefix_number) {
    prefix_size = prefix_number;
    prefix pr;
    std::string input_word;
    for (int i = 0; i < prefix_number; i++) {
        input >> input_word;
        pr.push_back(input_word);
    }
    first_prefix = pr;
    while (input >> input_word) {
        if (statetab.find(pr) == statetab.end())
            statetab[pr] = { input_word };
        else
            statetab[pr].push_back(input_word);
        pr.pop_front();
        pr.push_back(input_word);
    }
}

std::string TextGen::CreateText(int length) {
    return CreateText(length, std::default_random_engine::default_seed);
}

std::string TextGen::CreateText(int length, int seed) {
    std::default_random_engine rng(seed);
    std::string output;
    for (int i = 0; i < prefix_size; i++) {
        output += first_prefix[i] + " ";
    }
    prefix current_prefix = first_prefix;
    while (output.size() < length) {
        if (statetab.find(current_prefix) == statetab.end())
            break;
        std_distr dist(0, statetab[current_prefix].size() - 1);
        std::string suffix = statetab[current_prefix][dist(rng)];
        if (suffix == std::string())
            throw std::invalid_argument("dist out of range");
        output += suffix + " ";
        current_prefix.pop_front();
        current_prefix.push_back(suffix);
    }
    return output + "\n";
}

TextGen::TextGen(std::map<prefix, std::vector<std::string>> s) : statetab(s) {
    first_prefix = s.begin().operator*().first;
    prefix_size = first_prefix.size();
}

const std::map<TextGen::prefix, std::vector<std::string>>& TextGen::states() {
    return std::ref(statetab);
}
