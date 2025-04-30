// Copyright 2021 GHA Test Team
#include <iostream>
#include "textgen.h"

int main() {
  try {
    TextGenerator generator(2);
    generator.learnFromText(INPUT_FILE_PATH);
    generator.generateText(1000, OUTPUT_FILE_PATH);

    std::cout << "Text generated successfully in gen.txt" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
