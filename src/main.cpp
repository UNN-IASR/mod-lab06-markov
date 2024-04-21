// Copyright 2024 Alexander Sidelnikov

#include <fstream>
#include <sstream>

#include "textgen.h"

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;

    TextGenerator generator(NPREF);

    std::ifstream file("train.txt");
    generator.create_suffix_map(file);

    auto map = generator.get_suffix_map();

    std::string result = generator.generate(MAXGEN);

    std::ofstream out("generated.txt");
    out << result << std::endl;
}
