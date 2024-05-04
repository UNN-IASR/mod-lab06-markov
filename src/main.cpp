// Copyright 2024 Matvey Bobrov
#include <iostream>
#include <vector>
#include "textgen.h"

int main() {
    std::string text = ReadFile("data.txt");
    const int MAXGEN = 1000;
    const int NPREF = 2;
    std::string result = Generator().GenerateText(text, NPREF, MAXGEN);
    std::cout << result;
    return 0;
}
