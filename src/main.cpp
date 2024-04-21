// Copyright 2024 EltIsma

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
  TextGenerator generator;
  std::ifstream text("text.txt");
  generator.buildTable(text, NPREF);
  std::string new_text = generator.generate_text(MAXGEN);
  std::cout << new_text << std::endl;

  return 0;
}
