// Copyright 2024 CSB201

#include <iostream>
#include "textgen.h"

int main() {
    setlocale(LC_ALL, "Ru");

    std::string text;
    int sizePrefix;

    text = ReadFile("text.txt");

    std::cout << "Write size prefix: \n";
    std::cin >> sizePrefix;

    std::cout << "\n\nGenerate Text: \n\n";
    Markov markov = Markov(text, sizePrefix);

    std::string ans = markov.GenerateText(100);

    std::cout << ans;
}
