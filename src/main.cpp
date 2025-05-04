// Copyright 2021 GHA Test Team

#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "textgen.h"

using std::cerr;
using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::ifstream;
using std::map;
using std::string;
using std::vector;

const int NPREF = 2;
const int MAXGEN = 1000;

typedef deque<string> prefix;
map<prefix, vector<string>> statetab;

int main(int argc, char* argv[]) {
  string inputFile = "input.txt";
  string outputFile = "gen.txt";

  ifstream in(inputFile);
  if (!in) {
    cerr << "Ошибка открытия файла " << inputFile << endl;
    return 1;
  }

  try {
    TextGenerator generator;
    generator.build(in);
    generator.generate(MAXGEN, outputFile);
  } catch (const exception& e) {
    cerr << "Ошибка: " << e.what() << endl;
  }
  return 0;
}
