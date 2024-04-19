// Copyright 2024 Nekkozzz

#include "textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
    generator gen;
    std::ifstream file("text.txt");
    gen.train(file, NPREF);
    std::ofstream out("out.txt");
    out << gen.generate_text(MAXGEN) << std::endl;
}
