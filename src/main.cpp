// Copyright 2024 mpv-enjoyer
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "textgen.h"

const int MAXGEN = 1000;
const int NPREF = 1;

int main() {
    std::ifstream input("input.txt");
    TextGen textgen(input, NPREF);
    std::cout << textgen.CreateText(1000);
    return 0;
}
