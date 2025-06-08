// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "textgen.h"

static const int NPREF = 2;
static const int MAXGEN = 1000;

int main() {
    const std::string input_path = "input.txt";
    const std::string output_path = "gen.txt";

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::ifstream infile(input_path);
    if (!infile) {
        std::cerr << "Error opening input file: " << input_path << '\n';
        return 1;
    }

    statetab_t statetab;
    build_prefix_map(infile, statetab, NPREF);
    if (statetab.empty()) {
        std::cerr << "No prefixes loaded. Check input content.\n";
        return 1;
    }

    auto words = generate_text(statetab, NPREF, MAXGEN);

    std::ofstream outfile(output_path);
    if (!outfile) {
        std::cerr << "Error opening output file: " << output_path << '\n';
        return 1;
    }

    for (const auto& w : words) {
        outfile << w << " ";
    }
    outfile << '\n';

    std::cout << "Generated " << words.size()
              << " words into '" << output_path << "'.\n";
    return 0;
}
