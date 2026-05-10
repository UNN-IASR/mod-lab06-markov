#include "../include/textgen.h"
#include <fstream>
#include <iostream>
#include <filesystem>

const int NPREF = 2;
const int MAXGEN = 1000;

int main(int argc, char* argv[]) {
    std::cout << "ѕытаемс€ открыть: " << std::filesystem::absolute("../src/input.txt") << "\n";
    std::ifstream input("../src/input.txt");
    if (!input)
    {
        std::cout << "Can't find file";
        return 0;
    }
    statetab table;
    build_table(input, table, NPREF);
    generate_text(table, NPREF, MAXGEN);
    return 0;
}
