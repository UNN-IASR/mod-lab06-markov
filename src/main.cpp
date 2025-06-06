// Copyright 2025 9hkge

#include <fstream>
#include <string>
#include "textgen.h"

int main() {
  const int NPREF = 2;
  const int MAXGEN = 1000;

  TextGenerator generator(NPREF, 48);


  std::ifstream file("input_text.txt");
  generator.create_suffix_map(file);

  auto map = generator.get_suffix_map();

  std::string result = generator.generate(MAXGEN);

  const std::string output_filename = "result/gen.txt";
  std::ofstream outputFile(output_filename);

  outputFile << result;
  outputFile.close();

  return 0;
}
