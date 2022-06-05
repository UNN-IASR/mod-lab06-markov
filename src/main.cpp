// Copyright 2022 UNN
#include "textgen.h"

int main() {
    Generator gen = Generator("...\\Text.txt");
    std::cout << gen.newText() << std::endl;
}
