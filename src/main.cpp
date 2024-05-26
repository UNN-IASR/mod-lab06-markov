// Copyright 2024 UNN-IASR
#include "../include/textgen.h"

int main() {
    setlocale(LC_ALL, "Russian");
    build("input.txt", 2);
    std::string generated_text = generate_text(MAXGEN);
    std::cout << generated_text << std::endl;
    return 0;
}
