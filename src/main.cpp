#include "textgen.h"

int main() {
  TextGenerator tg("data.txt", 2);
  std::ofstream file("gen.txt");
  std::string text = tg.genText(1000);
  file << text;
  std::cout << text;
}