#include <iostream>
#include "textgen.h"

// Copyright 2024

int main() {
    TextGen tg = TextGen("../../input.txt");
    std::cout << tg.Generate(50);
    return 0;
}
