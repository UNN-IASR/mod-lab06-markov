// Copyright 2022 GHA Test Team

#include <iostream>
#include "textgen.h"

int main() {
    setlocale(LC_ALL, "Ru");

    std::string text = ReadFile("text.txt");
    std::string textForMarkov;

    for (char c : text) {
        if (c == '\n') {
            textForMarkov += "\n ";
        } else {
            textForMarkov += c;
        }
    }

    const int MAXGEN = 205;
    const int sizePref = 1;

    std::cout << "\n\nResult Text: \n\n";
    std::string ans = Markov().GenerateText(textForMarkov, sizePref, MAXGEN);

    std::cout << ans;
}
