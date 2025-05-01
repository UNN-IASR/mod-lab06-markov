// Copyright 2025 UNN
#include <ctime>
#include "textgen.h"

int main() {
    std::string filename = "what_is_autumn.txt";
    
    TextGen generator(filename);
    generator.Generate(filename, time(0));
    return 0;
}