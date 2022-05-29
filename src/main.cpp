// Copyright 2022 UNN-IASR
#include <fstream>
#include <iostream>
#include "textgen.h"

int main() {
    std::ifstream fin;
    fin.open("text.txt");
    if (!fin.is_open()) {
        std::cout << "Error!";
        exit(0);
    }
    std::vector<std::string> words;
    std::string word;
    while (!fin.eof()) {
        fin >> word;
        words.push_back(word);
    }
    fin.close();

    Markov Gen(words, 2, 1000);
    std::string line = Gen.TextGen();

    std::ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open()) {
        std::cout << "Error";
        exit(0);
    }
    fout.clear();
    fout << line;
    fout.close();

    return 1;
}
