// src/main.cpp
// Copyright 2025 ArriVeder4i
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "textgen.h"

static const int NPREF = 2;
static const int MAXGEN = 1500;

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error opening input.txt\n";
        return 1;
    }
    statetab_t tab;
    build_prefix_map(infile, tab, NPREF);

    auto words = generate_text(tab, NPREF, MAXGEN);

    std::ofstream outfile("gen.txt");
    if (!outfile) {
        std::cerr << "Error opening gen.txt\n";
        return 1;
    }
    for (const auto& w : words) {
        outfile << w << ' ';
    }
    outfile << '\n';
    std::cout << "Generated " << words.size() << " words.\n";
    return 0;
}
