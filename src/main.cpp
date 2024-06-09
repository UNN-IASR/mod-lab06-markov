// Copyright 2023 UNN-IASR

#include "textgen.h"

int main() {
    MarkovGenerator g = MarkovGenerator(2, 1000);
    g.readFromFile("input.txt");
    g.generateNewText();
}
