#include "textgen.h"
const int NPREF = 2;      // количество слов в префиксе
const int MAXGEN = 1000;  // объем текста на выходе
void TextGenerator::analyzeText(std::string filepath) {
  std::ifstream file(filepath);
  prefix pref;
  if (!file) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
  }
  for (int i = 0; i < prefix_len; i++) {
    std::string w;
    file >> w;
    pref.push_back(w);
  }
  init_pref = pref;
  std::string word;
  while (file >> word) {
    statetab[pref].push_back(word);
    pref.push_back(word);
    pref.pop_front();
  }
  end_pref = pref;
}
std::string TextGenerator::genText(int text_len = MAXGEN) {
  std::string text = "";
  prefix pref = init_pref;
  for (int i = 0; i < pref.size(); i++) {
    text += pref[i] + " ";
  }
  for (int i = 0; i < text_len; i++) {
    if (pref == end_pref) return text;
    std::string word = genSuffix(pref);
    text += word + " ";
    if (i % 20 == 0) text += "\n";
    pref.push_back(word);
    pref.pop_front();
  }
  return text;
}
std::string TextGenerator::genSuffix(prefix pref) {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<> distribution(0, statetab[pref].size() - 1);
  return statetab[pref][distribution(generator)];
}