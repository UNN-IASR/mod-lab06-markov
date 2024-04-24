// Copyright 2022 UNN-IASR
#include "textgen.h"
typedef std::deque<std::string> prefix;
int main() {
  setlocale(LC_ALL, "ru");
  std::string file = "skazka.txt";
  generator gen;
  std::vector<std::string>words = gen.read_vchodnoi_fail(file);
  std::map<prefix, std::vector<std::string>> tablica =
  gen.sozdaem_tablicu(words);
  std::string itog = gen.itogovii_text(tablica);
  return 0;
}
