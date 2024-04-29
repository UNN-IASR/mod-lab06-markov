// Copyright 2024 Mikhas3009

#include "textgen.h"

const int NPREF = 3;
const int MAXGEN = 500;

int main() {
    markov::MarkovChain generator;
    generator.train("text.txt", NPREF);
    std::string result = generator.generate(MAXGEN, true);
    std::ofstream file("output.txt");
    file << result;
}
