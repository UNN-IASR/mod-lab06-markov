// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "textgen.h"

int main() {
    TextGen t = TextGen("Text1.txt", 2);
    std::string text = t.CreateText(1000);
    std::cout << text;
}
