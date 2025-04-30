// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

TextGeneratorMarkov::TextGeneratorMarkov(int prefixSize, int maxWords)
    : NPREF(prefixSize), MAXGEN(maxWords) {
  std::random_device rd;
  gen.seed(rd());
}

void TextGeneratorMarkov::loadText(const std::string &filename) {
  std::ifstream inputFile(filename);
  if (!inputFile) {
    throw std::runtime_error("Cannot open input file: " + filename);
  }

  createStateTable(inputFile);
  inputFile.close();
}

void TextGeneratorMarkov::createStateTable(std::istream &input) {
  Prefix prefix;
  std::string word;

  for (int i = 0; i < NPREF; ++i) {
    if (input >> word) {
      prefix.push_back(word);
    }
  }

  while (input >> word) {
    addSuffix(prefix, word);
    prefix.pop_front();
    prefix.push_back(word);
  }
}

void TextGeneratorMarkov::addSuffix(const Prefix &prefix,
                                    const std::string &suffix) {
  auto it = statetab.find(prefix);
  if (it == statetab.end()) {
    statetab[prefix] = {suffix};
  } else {
    it->second.push_back(suffix);
  }
}

std::string TextGeneratorMarkov::getRandomSuffix(const Prefix &prefix) {
  const auto &suffixes = statetab[prefix];

  if (suffixes.empty()) {
    throw std::runtime_error("No suffixes available ");
  }

  return suffixes[std::uniform_int_distribution<size_t>{0, suffixes.size() -
                                                               1}(gen)];
}

void TextGeneratorMarkov::generateText(const std::string &outputFile) {
  if (statetab.empty()) {
    throw std::runtime_error("State table is empty.");
  }

  std::ofstream outFile(outputFile);
  if (!outFile) {
    throw std::runtime_error("Cannot open output file: " + outputFile);
  }

  std::uniform_int_distribution<> dis(0, statetab.size() - 1);
  auto it = statetab.begin();
  std::advance(it, dis(gen));
  Prefix prefix = it->first;

  for (const auto &word : prefix) {
    outFile << word << " ";
  }
  int wordCount = NPREF;

  while (wordCount < MAXGEN) {
    try {
      std::string suffix = getRandomSuffix(prefix);
      outFile << suffix << " ";

      prefix.pop_front();
      prefix.push_back(suffix);
      wordCount++;

      if (wordCount % 15 == 0)
        outFile << "\n";
    } catch (const std::runtime_error &) {
      it = statetab.begin();
      std::advance(it, dis(gen));
      prefix = it->first;
    }
  }

  outFile.close();
  std::cout << "Text generated and saved to " << outputFile
            << "Count words : " << wordCount << std::endl;
}