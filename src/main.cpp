// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "textgen.h"

int main() {
    textgen t = textgen("forTesting.txt", 2);
    std::string text = t.CreateText(1000);
    std::cout << text;
}
