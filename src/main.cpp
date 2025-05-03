#include <iostream>

#include "textgen.h"

using std::cout;
using std::endl;

int main() {
  TextGenerator generator("../input/source.txt");
  cout << generator.generateText() << endl;
  return 0;
}