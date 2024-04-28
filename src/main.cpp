//Copyright 2024 UNN-IASR
#include <iostream>
#include <fstream>
#include "textgen.h"

std::string readText(const std::string& name) {
    std::string intel;
    std::ifstream file(name);

    if (file.is_open()) {
        std::string str;
        while (std::getline(file, str)) {
            intel += str + " ";
        }
        intel.pop_back();
        file.close();
    }

    return intel;
}
int main() {
    const int NREF = 2;
    const int MAXGEN = 1000;

    std::string intext = readText("text.txt");

    TextGen gen;
    gen.create_tab(intext, NREF);

    std::string text = gen.generate(MAXGEN, 100);
    std::cout << text;
}
