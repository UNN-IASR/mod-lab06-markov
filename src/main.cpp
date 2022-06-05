// Copyright 2022 UNN-IASR
#include "textgen.h"

int main() {
    std::string line;
    std::string text = "text.txt";
    TextGenerator gentext = TextGenerator(text, 2, 1000);
    std::cout << gentext.generate();
}
