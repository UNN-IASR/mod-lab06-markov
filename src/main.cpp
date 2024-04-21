// Copyright 2024 Vladislav Labutin

#include "textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
    markov generator;
    generator.train("in.txt", NPREF);
    std::string result = generator.generate(MAXGEN, true);
    std::ofstream file("out.txt");
    file << result;
}
