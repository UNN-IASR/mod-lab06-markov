#include <iostream>

#include "textgen.h"

using std::cout;
using std::endl;

int main() {
  TextGenerator generator("../input/source.txt");
  cout << generator.generateText("../../result/gen.txt") << endl;
  return 0;
}