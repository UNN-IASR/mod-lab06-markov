// Copyright 2022 UNN-IASR
#include <iostream>
#include<fstream>
#include<locale>
#include"textgen.h"
int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;
    const int seed = 100;
    setlocale(LC_ALL, "rus");
    std::ifstream file("text.txt");
    std::vector<std::string>words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    MarkovChain markov;
    markov.Tab(words, NPREF);
    std::cout << markov.CreateText(MAXGEN, seed);
}
