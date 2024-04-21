// Copyright 2024 Ignatyev Artyom

#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
    Generator generator;
    std::ifstream file("in.txt");
    generator.createStatetab(file, NPREF);
    std::ofstream out("out.txt");
    out << generator.generateText(MAXGEN) << std::endl;
}
