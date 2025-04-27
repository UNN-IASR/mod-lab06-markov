// Copyright 2022 UNN-IASR
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "textgen.h"

int main() {
  const std::string input_file = "../../src/input.txt";
  const int NPREF = 2;
  const int MAXGEN = 1000;

  TextGenerator generator;
  generator.createTable(input_file, NPREF);

  const std::string out_file = "../../result/gen.txt";
  generator.generateText(MAXGEN, out_file);

  return 0;
}
