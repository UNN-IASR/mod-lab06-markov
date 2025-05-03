#include <iostream>

#include "textgen.h"

using std::cout;
using std::endl;

int main() {
  TextGenerator generator("../input/source.txt");
  generator.printTable();
  return 0;
}