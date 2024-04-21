// Copyright 2024 Kapochkin Mikhail

#include <iostream>
#include <fstream>
#include "textgen.h"
const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

int main() {
    std::ifstream input_stream("test.txt");
    std::string string, line;
    while (std::getline(input_stream, line)) {
        string += line + " ";
    }
    TextGen textgen;
    textgen.CreateStatetabPrefixes(string, NPREF);
    std::cout << textgen.GenerateText(time(0), MAXGEN);
}


