#include <iostream>

#include "textgen.h"

using std::cout;
using std::endl;

int main() {
  TextGenerator generator("../input/source.txt");
  cout << generator.getTable() << endl;
  cout << generator.generateText("../../result/gen.txt", 1000) << endl;
  return 0;
}