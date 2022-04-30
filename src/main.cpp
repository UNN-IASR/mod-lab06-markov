// Copyright 2022 Dacyto

#include <iostream>
#include <fstream>
#include <ctime>

#include "textgen.h"

int main() {
    MarkovGenerator gen = MarkovGenerator("input.txt", NPREF);
    std::cout << gen.getText(MAXGEN) << std::endl;
}
