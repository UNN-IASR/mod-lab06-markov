// Copyright 2025 UNN
#include <ctime>
#include <string>
#include "textgen.h"

int main() {
    std::string filename = "golden_fish.txt";
    std::string resultname = "gen.txt";
    TextGen generator(filename);
    generator.Generate(resultname, time(0));
    return 0;
}
