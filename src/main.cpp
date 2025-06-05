// Copyright 2025 9hkge

#include "textgen.h"
#include <fstream>
#include <sstream>

int main() {

    const int NPREF = 2;
    const int MAXGEN = 1000;

    TextGenerator generator(NPREF);

    std::ifstream file("input_text.txt");
    generator.create_suffix_map(file);

    auto map = generator.get_suffix_map();

    std::string result = generator.generate(MAXGEN);

    std::ofstream out("generated.txt");
    out << result << std::endl;
}