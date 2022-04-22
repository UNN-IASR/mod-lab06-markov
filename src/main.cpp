// Copyright 2022 UNN-IASR
#include "textgen.h"

int main() {
    MarkovGenerator gen = MarkovGenerator("test.txt", NPREF);
    std::cout << gen.getText(MAXGEN) << std::endl;
}
