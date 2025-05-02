// Copyright 2025 sdanils
#include <iostream>
#include <string>

using std::string;

#include "textgen.h"

int main() {
  try {
    TextGenerator tg;
    string text = tg.generateText();
    TextReader::saveText(text);
  } catch (std::exception& e) {
    std::cout << e.what();
  }
}
