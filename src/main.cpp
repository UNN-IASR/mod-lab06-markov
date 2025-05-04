// Copyright 2022 UNN-IASR
#include <iostream>
#include <fstream>
#include <string>

#include "textgen.h"

int main() {
    TextGenerator tg("data.txt", 2);
    std::ofstream file("gen.txt");
    std::string text = tg.GenerateText(1000);
    file << text;
    std::cout << text;
    return 0;
}