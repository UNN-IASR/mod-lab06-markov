// Copyright 2024 Burdeiniy Artem
#include <iostream>
#include <vector>
#include "textgen.h"

int main() {
    setlocale(LC_ALL, "Rus");
    std::string text = ReadFile("data.txt");
    const int maxLength = 500;
    const int countPrefix = 2;
    std::string result = Generator().GenerateText(text, countPrefix, maxLength);
    std::cout << result;
    return 0;
}
