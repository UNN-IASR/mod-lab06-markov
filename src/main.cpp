// Copyright 2024 Choncharova Anna
#include <iostream>
#include <fstream>
#include <sstream>
#include "textgen.h"

int main() {
    const int NREF = 2;
    const int MAXGEN = 1000;
    std::string text;
    std::string line;
    std::ifstream file("text.txt");
    while (std::getline(file, line)) {
        text += line + " ";
    }
    Generator gen;
    gen.creating_statetab(text, NREF);
    std::cout << gen.Text_generator(MAXGEN, time(0));
}
