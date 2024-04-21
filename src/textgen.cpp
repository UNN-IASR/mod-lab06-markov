//Copyright 2024 <levkovich-polina>
#include "textgen.h"

std::map<std::string, std::vector<std::string>> text::read(
    std::string filename,
    const std::map<std::string, std::vector<std::string>>& markovChain,
    int prefixLength) {
  std::ifstream file(filename);
  std::map<std::string, std::vector<std::string>> Chain = markovChain;
  if (file.is_open()) {
    std::string word;

    while (file >> word) {
      if (prefix.size() < prefixLength) {
        prefix.push_back(word);
        continue;
      }
      std::string key = "";
      for (int i = 0; i < prefix.size() - 1; i++) {
        key += prefix[i] + " ";
      }
      key += prefix.back();

      Chain[key].push_back(word);
      prefix.erase(prefix.begin());
      prefix.push_back(word);
      stop = key;
    }
    file.close();
  }
  return Chain;
}
void text::generate(
    const std::map<std::string, std::vector<std::string>> markovChain,
    int prefixLength, int textLength) {
  std::map<std::string, std::vector<std::string>> Chain = markovChain;
  generateText = "";
  srand(time(NULL));
  int index = std::rand() % markovChain.size();
  auto it = markovChain.begin();
  for (int i = 0; i < index; i++) {
    it++;
  }
  std::string key = it->first;
  generateText += key + " ";
  std::cout << key << " ";

  int i = 0;

  std::string nextWord;
  while (i < textLength - prefixLength && key != stop) {
    std::vector<std::string> possibleWords = Chain[key];
    nextWord = possibleWords[rand() % possibleWords.size()];
    std::cout << nextWord << " ";
    generateText += nextWord;
    if (prefixLength > 1)
      key = key.substr(key.find(" ") + 1) + " " + nextWord;
    else
      key = nextWord;
    i++;
  }
  std::cout << std::endl;
}
