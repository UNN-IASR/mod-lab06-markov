//Copyright 2024 <levkovich-polina>
#include <iostream>

#include "textgen.h"

int main() {
  setlocale(LC_ALL, "ru-Ru");

  std::string filename = "data.txt";

  int prefixLength = 2;

  int textLength = 500;

  std::map<std::string, std::vector<std::string>> markovChain;

  text text;
  text.read(filename, markovChain, prefixLength);

  text.generate(markovChain, prefixLength, textLength);

  return 0;
}
