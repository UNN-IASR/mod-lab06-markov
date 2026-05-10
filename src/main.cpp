//Copyright 2026 EnganK

#include <fstream>
#include <iostream>
#include <random>
#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main(int argc, char* argv[]) {
    std::ifstream input("../src/input.txt");
    if (!input) {
        std::cout << "Can't find file";
        return 0;
    }
    statetab table;
    build_table(input, table, NPREF);
    std::random_device rd;
    std::mt19937 gen(rd());
    generate_text(table, NPREF, MAXGEN, gen);
    return 0;
}
