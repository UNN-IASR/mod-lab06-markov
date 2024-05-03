// Copyright 2024 katione
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "textgen.h"

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;
    std::string line;
    std::string str;
    std::ifstream input("text.txt.txt");
    if (!input) {
        std::cout << "Error!" << std::endl;
    }
    while (std::getline(input, line)) {
        str += line + " ";
    }
    Text_Gen text_gen;
    text_gen.text_file(NPREF, str);
    std::string result = text_gen.text_generation(MAXGEN, time(0));
    std::ofstream out("outtext.txt");
    out << result << std::endl;
    std::cout << result;
    return 0;
}
